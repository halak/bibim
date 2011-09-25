namespace Bibim
{
    const String& AssetStreamReader::GetName() const
    {
        return name;
    }

    GameModuleTree* AssetStreamReader::GetModules() const
    {
        return modules;
    }

    bool AssetStreamReader::IsPriority() const
    {
        return isPriority;
    }
}