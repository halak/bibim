namespace Bibim
{
    GameModuleTree* AssetReader::GetModules() const
    {
        return modules;
    }

    bool AssetReader::operator == (const AssetReader& right) const
    {
        return BinaryReader::operator == (right) && modules == right.modules;
    }

    bool AssetReader::operator != (const AssetReader& right) const
    {
        return !operator == (right);
    }
}