namespace Bibim
{
    const String& AssetLoadingTask::GetName() const
    {
        return name;
    }

    uint AssetLoadingTask::GetTotalBytes() const
    {
        return totalBytes;
    }

    uint AssetLoadingTask::GetLoadedBytes() const
    {
        return loadedBytes;
    }

    void AssetLoadingTask::SetLoadedBytes(uint value)
    {
        loadedBytes = value;
    }

    void AssetLoadingTask::AddLoadedBytes(uint value)
    {
        loadedBytes += value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GameAssetStorage* AssetPreloadingTask::GetStorage() const
    {
        return storage;
    }
}