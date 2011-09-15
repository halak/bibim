#include <Bibim/PCH.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/Assert.h>
#include <Bibim/AssetProvider.h>
#include <algorithm>

namespace Bibim
{
    GameAssetStorage::GameAssetStorage()
    {
    }

    GameAssetStorage::~GameAssetStorage()
    {
    }

    GameAsset* GameAssetStorage::Load(const String& name)
    {
        AssetTable::iterator it = assets.find(name);
        if (it != assets.end())
            return (*it).second;
        else
        {
            for (ProviderCollection::const_iterator it = providers.begin(); it != providers.end(); it++)
            {
                if (GameAsset* asset = (*it)->Load(name))
                {
                    assets.insert(AssetTable::value_type(name, asset));
                    return asset;
                }
            }

            return nullptr;
        }
    }

    void GameAssetStorage::Add(AssetProvider* item)
    {
        BBAssertDebug(std::find(providers.begin(), providers.end(), item) == providers.end());

        providers.push_back(item);
    }

    void GameAssetStorage::Remove(AssetProvider* item)
    {
        ProviderCollection::iterator it = std::find(providers.begin(), providers.end(), item);
        BBAssertDebug(it != providers.end());

        providers.erase(it);
    }
}