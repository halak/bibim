namespace Bibim
{
    const String& AssetLoadingTask::GetName() const
    {
        return name;
    }

    int AssetLoadingTask::GetTotalBytes() const
    {
        return totalBytes;
    }

    int AssetLoadingTask::GetLoadedBytes() const
    {
        return loadedBytes;
    }

    void AssetLoadingTask::SetLoadedBytes(int value)
    {
        loadedBytes = value;
    }

    void AssetLoadingTask::AddLoadedBytes(int value)
    {
        loadedBytes += value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GameAssetStorage* AssetPreloadingTask::GetStorage() const
    {
        return storage;
    }
}