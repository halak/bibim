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

    GameAssetStorage* AssetStreamReader::GetStorage() const
    {
        return storage;
    }

    bool AssetStreamReader::IsPriority() const
    {
        return isPriority;
    }
}