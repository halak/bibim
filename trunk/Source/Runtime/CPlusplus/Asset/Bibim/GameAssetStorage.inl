namespace Bibim
{
    const GameAssetStorage::AssetTable& GameAssetStorage::GetAssets() const
    {
        return assets;
    }

    const GameAssetStorage::ProviderCollection& GameAssetStorage::GetProviders() const
    {
        return providers;
    }
}