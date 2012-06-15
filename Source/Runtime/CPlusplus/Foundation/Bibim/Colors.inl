namespace Bibim
{
    Colors::Item::Item()
        : Name(String::Empty),
          Value(0, 0, 0, 0)
    {
    }

    Colors::Item::Item(const String& name, Color color)
        : Name(name),
          Value(color)
    {
    }

    Colors::Item::Item(const Item& original)
        : Name(original.Name),
          Value(original.Value)          
    {
    }

    Colors::Item& Colors::Item::operator = (const Item& right)
    {
        Name = right.Name;
        Value = right.Value;
        return *this;
    }

    bool Colors::Item::operator == (const Item& right) const
    {
        return Name == right.Name && Value == right.Value;
    }

    bool Colors::Item::operator != (const Item& right) const
    {
        return !operator == (right);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const Colors::ItemCollection& Colors::GetItems()
    {
        return items;
    }
}