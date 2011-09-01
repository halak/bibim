namespace Bibim
{
    const String& GameModule::GetName() const
    {
        return name;
    }

    void GameModule::SetName(const String& value)
    {
        name = value;
    }

    const String& GameModule::GetFilename() const
    {
        return filename;
    }
    
    void GameModule::SetFilename(const String& value)
    {
        filename = value;
    }
    
    const String& GameModule::GetDescription() const
    {
        return description;
    }

    void GameModule::SetDescription(const String& value)
    {
        description = value;
    }
}