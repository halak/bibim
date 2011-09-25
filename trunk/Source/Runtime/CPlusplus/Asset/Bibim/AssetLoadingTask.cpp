#include <Bibim/AssetLoadingTask.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    AssetLoadingTask::AssetLoadingTask(const String& name, uint totalBytes)
        : name(name),
          totalBytes(totalBytes),
          loadedBytes(0)
    {
    }

    AssetLoadingTask::~AssetLoadingTask()
    {
        BBAssertDebug(totalBytes >= loadedBytes);
    }

    void AssetLoadingTask::Cancel()
    {
    }

    bool AssetLoadingTask::IsPreloading() const
    {
        return true;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    AssetPreloadingTask::AssetPreloadingTask(const String& name, GameAssetStorage* storage)
        : AssetLoadingTask(name, 0),
          storage(storage)
    {
        BBAssert(storage);
    }

    AssetPreloadingTask::~AssetPreloadingTask()
    {
    }

    bool AssetPreloadingTask::IsPreloading() const
    {
        return true;
    }

    void AssetPreloadingTask::Register(GameAsset* asset)
    {
        storage->SetAsset(GetName(), asset);
    }
}