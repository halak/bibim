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

    bool AssetStreamReader::operator == (const AssetStreamReader& right) const
    {
        return BinaryReader::operator == (right) && name == right.name && storage == right.storage && modules == right.modules;
    }

    bool AssetStreamReader::operator != (const AssetStreamReader& right) const
    {
        return !operator == (right);
    }
}