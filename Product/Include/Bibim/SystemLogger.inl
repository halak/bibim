namespace Bibim
{
    const String& SystemLogger::GetName() const
    {
        return name;
    }

    void SystemLogger::SetName(const String& value)
    {
        name = value;   
    }
}