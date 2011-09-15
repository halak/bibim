#pragma once
#ifndef __BIBIM_GAMEASSETSTORAGE_H__
#define __BIBIM_GAMEASSETSTORAGE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/String.h>
#   include <map>
#   include <vector>

    namespace Bibim
    {
        class GameAssetStorage : public GameModule
        {
            public:
                typedef std::map<String, GameAsset*> AssetTable;
                typedef std::vector<AssetProvider*> ProviderCollection;

            public:
                GameAssetStorage();
                virtual ~GameAssetStorage();

                GameAsset* Load(const String& name);

                inline const AssetTable& GetAssets() const;
                inline const ProviderCollection& GetProviders() const;

            private:
                void Add(AssetProvider* item);
                void Remove(AssetProvider* item);

            private:
                AssetTable assets;
                ProviderCollection providers;

                friend class AssetProvider;
        };
    }

#endif