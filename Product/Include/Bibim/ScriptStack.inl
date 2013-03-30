namespace Bibim
{
    byte* ScriptStack::Peek()
    {
        int t = 0;
        return Peek(t);
    }

    const byte* ScriptStack::Peek() const
    {
        int t = 0;
        return Peek(t);
    }

    int ScriptStack::GetTopIndex() const
    {
        return static_cast<int>(offsetStack.size()) - 1;
    }

    int ScriptStack::GetCapacity() const
    {
        return static_cast<int>(buffer.capacity());
    }

    bool ScriptStack::IsEmpty() const
    {
        return offsetStack.empty();
    }
}