namespace Bibim
{
    GameModuleTree* AssetReader::GetModules() const
    {
        return modules;
    }

    bool AssetReader::operator == (const AssetReader& right) const
    {
        return BinaryReader::operator == (right) && storage == right.storage && modules == right.modules;
    }

    bool AssetReader::operator != (const AssetReader& right) const
    {
        return !operator == (right);
    }
}