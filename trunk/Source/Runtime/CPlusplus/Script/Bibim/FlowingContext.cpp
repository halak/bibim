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
            throw Exception("�̹� �������Դϴ�.");
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
            throw Exception("�̹� �������Դϴ�.");
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
                // ���������� �����ų� �ߴ�(Break) �Ǿ����ϴ�.
                current.Reset();
                status = FinishedStatus;
                break;
            case SuspendedStatus:
                // �Ͻ������� ����(Yield) �Ǿ����ϴ�.
                // Current�� �����մϴ�.
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