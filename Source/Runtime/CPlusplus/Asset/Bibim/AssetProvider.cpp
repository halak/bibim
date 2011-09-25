#include <Bibim/PCH.h>
#include <Bibim/AssetProvider.h>
#include <Bibim/AssetLoadingTask.h>
#include <Bibim/GameAssetStorage.h>

namespace Bibim
{
    AssetProvider::AssetProvider()
        : storage(nullptr)
    {
    }

    AssetProvider::AssetProvider(GameAssetStorage* storage)
        : storage(storage)
    {
        if (storage)
            storage->Add(this);
    }

    AssetProvider::~AssetProvider()
    {
        if (storage)
            storage->Remove(this);
    }

    void AssetProvider::SetStorage(GameAssetStorage* value)
    {
        if (storage != value)
        {
            if (storage)
                storage->Remove(this);

            storage = value;

            if (storage)
                storage->Add(this);
        }
    }
    
    void AssetProvider::Add(AssetPreloadingTask* item)
    {
        BBAssert(storage);
        storage->AddLast(item);
    }
}