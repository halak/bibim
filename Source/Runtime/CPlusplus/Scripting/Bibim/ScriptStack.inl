namespace Bibim
{
    const ScriptStack::Items& ScriptStack::GetItems() const
    {
        return items;
    }

    int ScriptStack::GetTopIndex() const
    {
        return topIndex;
    }

    int ScriptStack::GetCapacity() const
    {
        return items.size();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool ScriptStack::Item::operator != (const Item& right) const
    {
        return !operator == (right);
    }
}