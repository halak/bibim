namespace Bibim
{
    Timeline::Item::Item()
        : RawPointer(nullptr),
          SharedPointer()
    {
    }

    Timeline::Item::Item(IUpdateable* item)
        : RawPointer(item),
          SharedPointer()
    {
    }

    Timeline::Item::Item(IUpdateablePtr item)
        : RawPointer(item.GetPointee()),
          SharedPointer(item)
    {
    }

    bool Timeline::Item::operator == (const Item& right) const
    {
        return RawPointer == right.RawPointer;
    }

    bool Timeline::Item::operator != (const Item& right) const
    {
        return !operator == (right);
    }
}