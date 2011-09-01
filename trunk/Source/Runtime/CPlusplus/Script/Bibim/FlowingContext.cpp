#include <Bibim/PCH.h>
#include <Bibim/FlowingContext.h>
#include <Bibim/Assert.h>
#include <Bibim/Flowchart.h>
#include <Bibim/FlowchartBlock.h>
#include <Bibim/VariableStorage.h>
#include <Bibim/Any.h>
#include <stdexcept>

namespace Bibim
{
    FlowingContext::FlowingContext(FlowchartPtr source)
        : source(source),
          status(FinishedStatus),
          variables(new VariableStorage())
    {
    }

    FlowingContext::FlowingContext(FlowchartPtr source, VariableStoragePtr parentVariables)
        : source(source),
          status(FinishedStatus),
          variables(new VariableStorage(parentVariables))
    {
    }

    FlowingContext::~FlowingContext()
    {
    }
    
    void FlowingContext::Execute()
    {
        if (GetStatus() == ExecutingStatus)
            throw Exception("이미 실행중입니다.");
        if (GetStatus() == SuspendedStatus)
        {
            Resume(Any::Null);
            return;
        }

        ExecuteActually(source->GetStartupBlock());
    }

    void FlowingContext::Resume(const Any& result)
    {
        if (GetStatus() == ExecutingStatus)
            throw Exception("이미 실행중입니다.");
        if (GetStatus() == FinishedStatus)
        {
            Execute();
            return;
        }

        BBAssert(current);

        if (FlowchartBlockPtr block = current->FindNextBlock(result))
            ExecuteActually(block);
        else
            throw BadArgumentException("result");
    }

    void FlowingContext::ExecuteActually(FlowchartBlockPtr next)
    {
        status = ExecutingStatus;

        while (next)
        {
            current = next;
            next = current->Execute(*this);
        }

        switch (GetStatus())
        {
            case ExecutingStatus:
            case FinishedStatus:
                // 정상적으로 끝나거나 중단(Break) 되었습니다.
                current.Reset();
                status = FinishedStatus;
                break;
            case SuspendedStatus:
                // 일시적으로 중지(Yield) 되었습니다.
                // Current를 유지합니다.
                break;
        }
    }

    const Any& FlowingContext::Yield()
    {
        status = SuspendedStatus;
        return Any::Missing;
    }

    const Any& FlowingContext::Break()
    {
        status = FinishedStatus;
        return Any::Missing;
    }

    FlowchartPtr FlowingContext::GetSource() const
    {
        return source;
    }

    FlowchartBlockPtr FlowingContext::GetCurrent() const
    {
        return current;
    }

    FlowingContext::Status FlowingContext::GetStatus() const
    {
        return status;
    }

    VariableStoragePtr FlowingContext::GetVariables() const
    {
        return variables;
    }
}