namespace Bibim
{
    const String& AssetReader::GetName() const
    {
        return name;
    }

    GameModuleTree* AssetReader::GetModules() const
    {
        return modules;
    }

    bool AssetReader::operator == (const AssetReader& right) const
    {
        return BinaryReader::operator == (right) && name == right.name && storage == right.storage && modules == right.modules;
    }

    bool AssetReader::operator != (const AssetReader& right) const
    {
        return !operator == (right);
    }
}