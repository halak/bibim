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
        return BinaryReader::ToInt(thread->GetStack().GetAt(index - numberOfArguments));
    }

    longint ScriptingContext::GetLongIntArg(int index) const
    {
        BBAssertDebug(0 <= index && index < numberOfArguments);
        return BinaryReader::ToLongInt(thread->GetStack().GetAt(index - numberOfArguments));
    }

    float ScriptingContext::GetFloatArg(int index) const
    {
        BBAssertDebug(0 <= index && index < numberOfArguments);
        return BinaryReader::ToFloat(thread->GetStack().GetAt(index - numberOfArguments));
    }

    Color ScriptingContext::GetColorArg(int index) const
    {
        BBAssertDebug(0 <= index && index < numberOfArguments);
        return BinaryReader::ToColor(thread->GetStack().GetAt(index - numberOfArguments));
    }

    String ScriptingContext::GetStringArg(int index) const
    {
        BBAssertDebug(0 <= index && index < numberOfArguments);
        const int stringIndex = BinaryReader::ToInt(thread->GetStack().GetAt(index - numberOfArguments));
        return thread->GetScript()->GetStringTable()[stringIndex];
    }

    void ScriptingContext::Return()
    {
        BBAssert(numberOfReturnValues == 0 && returnCalled == false);
        returnCalled = true;
    }

    void ScriptingContext::YieldReturn()
    {
        // Native 함수에서 YieldReturn은 Call-stack에 Native 함수가 딱 하나일 때만 가능합니다.
        // Script call -> Native call -> Script call -> Native 이 상황에서 YieldReturn을 하면 thread-stack 엉켜 제대로 작동하지 않습니다.
        BBAssert(thread->GetNativeFunctionDepth() == 1);
        thread->SetState(ScriptThread::Suspended);
    }

    Any ScriptingContext::Call(const String& name)
    {
        return thread->Call(name);
    }

    Any ScriptingContext::Call(const String& name, const Any& arg1)
    {
        return thread->Call(name, arg1);
    }

    Any ScriptingContext::Call(const String& name, const Any& arg1, const Any& arg2)
    {
        return thread->Call(name, arg1, arg2);
    }

    Any ScriptingContext::Call(const String& name, const Any& arg1, const Any& arg2, const Any& arg3)
    {
        return thread->Call(name, arg1, arg2, arg3);
    }

    Any ScriptingContext::Call(const String& name, const Any& arg1, const Any& arg2, const Any& arg3, const Any& arg4)
    {
        return thread->Call(name, arg1, arg2, arg3, arg4);
    }

    Any ScriptingContext::Call(const String& name, const Any& arg1, const Any& arg2, const Any& arg3, const Any& arg4, const Any& arg5)
    {
        return thread->Call(name, arg1, arg2, arg3, arg4, arg5);
    }

    const Any& ScriptingContext::GetGlobal(int id) const
    {
        return thread->GetGlobal(id);
    }

    void ScriptingContext::SetGlobal(int id, const Any& value)
    {
        thread->SetGlobal(id, value);
    }
}