#include <Bibim/PCH.h>
#include <Bibim/ScriptingContext.h>
#include <Bibim/Assert.h>
#include <Bibim/BinaryReader.h>
#include <Bibim/Script.h>
#include <Bibim/ScriptThread.h>

namespace Bibim
{
    ScriptingContext::ScriptingContext(ScriptThread* thread, int numberOfArguments, int numberOfReturnValues)
        : thread(thread),
          numberOfArguments(numberOfArguments),
          numberOfReturnValues(numberOfReturnValues),
          returnCalled(false)
    {
    }

    ScriptingContext::~ScriptingContext()
    {
        BBAssert(numberOfReturnValues == 0 || returnCalled);
    }

    bool ScriptingContext::GetBoolArg(int index) const
    {
        BBAssertDebug(0 <= index && index < numberOfArguments);
        return BinaryReader::ToBool(thread->GetStack().GetAt(index - numberOfArguments));
    }

    int ScriptingContext::GetIntArg(int index) const
    {
        BBAssertDebug(0 <= index && index < numberOfArguments);
        return BinaryReader::ToInt32(thread->GetStack().GetAt(index - numberOfArguments));
    }

    uint ScriptingContext::GetUIntArg(int index) const
    {
        BBAssertDebug(0 <= index && index < numberOfArguments);
        return BinaryReader::ToUInt32(thread->GetStack().GetAt(index - numberOfArguments));
    }

    int64 ScriptingContext::GetLongIntArg(int index) const
    {
        BBAssertDebug(0 <= index && index < numberOfArguments);
        return BinaryReader::ToInt64(thread->GetStack().GetAt(index - numberOfArguments));
    }

    float ScriptingContext::GetFloatArg(int index) const
    {
        BBAssertDebug(0 <= index && index < numberOfArguments);
        return BinaryReader::ToFloat(thread->GetStack().GetAt(index - numberOfArguments));
    }

    String ScriptingContext::GetStringArg(int index) const
    {
        BBAssertDebug(0 <= index && index < numberOfArguments);
        const int stringIndex = BinaryReader::ToInt32(thread->GetStack().GetAt(index - numberOfArguments));
        return thread->GetScript()->GetStringTable()[stringIndex];
    }

    void ScriptingContext::Return()
    {
        BBAssert(numberOfReturnValues == 0 && returnCalled == false);
        returnCalled = true;
    }

    void ScriptingContext::Return(const ScriptObject& value)
    {
        BBAssert(numberOfReturnValues == 1 && returnCalled == false);
        returnCalled = true;

        throw;
    }

    void ScriptingContext::Return(const ScriptObject& value1, const ScriptObject& value2)
    {
        BBAssert(numberOfReturnValues == 2 && returnCalled == false);
        returnCalled = true;

        throw;
    }

    void ScriptingContext::Return(const ScriptObject& value1, const ScriptObject& value2, const ScriptObject& value3)
    {
        BBAssert(numberOfReturnValues == 3 && returnCalled == false);
        returnCalled = true;

        throw;
    }

    void ScriptingContext::Return(const ScriptObject& value1, const ScriptObject& value2, const ScriptObject& value3, const ScriptObject& value4)
    {
        BBAssert(numberOfReturnValues == 4 && returnCalled == false);
        returnCalled = true;

        throw;
    }

    void ScriptingContext::Return(const ScriptObject& value1, const ScriptObject& value2, const ScriptObject& value3, const ScriptObject& value4, const ScriptObject& value5)
    {
        BBAssert(numberOfReturnValues == 5 && returnCalled == false);
        returnCalled = true;

        throw;
    }

    void ScriptingContext::YieldReturn()
    {
        // Native 함수에서 YieldReturn은 Call-stack에 Native 함수가 딱 하나일 때만 가능합니다.
        // Script call -> Native call -> Script call -> Native 이 상황에서 YieldReturn을 하면 thread-stack 엉켜 제대로 작동하지 않습니다.
        BBAssert(thread->GetNativeFunctionDepth() == 1);
        thread->SetState(ScriptThread::Suspended);
    }

    ScriptObject ScriptingContext::Call(const String& name)
    {
        return thread->Call(name);
    }

    ScriptObject ScriptingContext::Call(const String& name, const ScriptObject& arg1)
    {
        return thread->Call(name, arg1);
    }

    ScriptObject ScriptingContext::Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2)
    {
        return thread->Call(name, arg1, arg2);
    }

    ScriptObject ScriptingContext::Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3)
    {
        return thread->Call(name, arg1, arg2, arg3);
    }

    ScriptObject ScriptingContext::Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4)
    {
        return thread->Call(name, arg1, arg2, arg3, arg4);
    }

    ScriptObject ScriptingContext::Call(const String& name, const ScriptObject& arg1, const ScriptObject& arg2, const ScriptObject& arg3, const ScriptObject& arg4, const ScriptObject& arg5)
    {
        return thread->Call(name, arg1, arg2, arg3, arg4, arg5);
    }

    const ScriptObject& ScriptingContext::GetGlobalVariable(uint id) const
    {
        return thread->GetGlobalVariable(id);
    }

    void ScriptingContext::SetGlobalVariable(uint id, const ScriptObject& value)
    {
        thread->SetGlobalVariable(id, value);
    }
}