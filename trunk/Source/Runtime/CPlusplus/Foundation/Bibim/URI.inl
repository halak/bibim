namespace Bibim
{
    URI::Source URI::GetSource() const
    {
        return source;
    }

    uint32 URI::GetID() const
    {
        return id;
    }

    const String& URI::GetAddress() const
    {
        return address;
    }

    bool URI::operator == (const URI& right) const
    {
        return source == right.source && id == right.id && address == right.address;
    }

    bool URI::operator != (const URI& right) const
    {
        return !operator == (right);
    }

    bool URI::operator < (const URI& right) const
    {
        return source < right.source && id < right.id && address < right.address;
    }
}