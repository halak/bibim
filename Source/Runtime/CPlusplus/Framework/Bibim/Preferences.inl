namespace Bibim
{
    const String& Preferences::GetName() const
    {
        return name;
    }

    bool Preferences::IsModified() const
    {
        return isModified;
    }

    bool Preferences::IsLoaded() const
    {
        return isLoaded;
    }

    bool Preferences::CanStore(Any::Type type)
    {
        switch (type)
        {
            case Any::BoolType:
            case Any::IntType:
            case Any::StringType:
                return true;
            default:
                return false;
        }
    }
}