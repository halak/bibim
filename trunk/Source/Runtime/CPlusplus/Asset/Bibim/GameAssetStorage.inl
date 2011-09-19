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

    void GameAssetStorage::ResetBackgroundLoadingStatus()
    {
        return loadingThread.ResetBackgroundLoadingStatus();
    }

    GameAssetStorage::LoadingStatus GameAssetStorage::GetBackgroundLoadingStatus()
    {
        return loadingThread.GetBackgroundLoadingStatus();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool GameAssetStorage::LoadingStatus::operator != (const LoadingStatus& right) const
    {
        return !operator == (right);
    }
}