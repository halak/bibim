namespace Bibim
{
    GameModuleTree* GameAssetStorage::GetModules() const
    {
        return modules;
    }

    void GameAssetStorage::SetModules(GameModuleTree* value)
    {
        modules = value;
    }

    const GameAssetStorage::AssetTable& GameAssetStorage::GetAssets() const
    {
        return assets;
    }

    const GameAssetStorage::ProviderCollection& GameAssetStorage::GetProviders() const
    {
        return providers;
    }
}