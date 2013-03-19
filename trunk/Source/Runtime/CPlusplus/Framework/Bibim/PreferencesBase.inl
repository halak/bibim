namespace Bibim
{
    const String& PreferencesBase::GetName() const
    {
        return name;
    }

    bool PreferencesBase::IsModified() const
    {
        return isModified;
    }

    bool PreferencesBase::IsLoaded() const
    {
        return isLoaded;
    }

    bool PreferencesBase::CanStore(Any::Type type)
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