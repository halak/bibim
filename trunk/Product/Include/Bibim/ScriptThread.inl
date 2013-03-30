namespace Bibim
{
    Script* ScriptThread::GetScript() const
    {
        return script;
    }

    const ScriptStack& ScriptThread::GetStack() const
    {
        return stack;
    }

    ScriptThread::State ScriptThread::GetState() const
    {
        return state;
    }

    void ScriptThread::SetState(State value)
    {
        state = value;
    }

    int ScriptThread::GetNativeFunctionDepth() const
    {
        return nativeFunctionDepth;
    }
}