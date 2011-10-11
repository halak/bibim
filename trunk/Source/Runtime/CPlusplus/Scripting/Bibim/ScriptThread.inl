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
}