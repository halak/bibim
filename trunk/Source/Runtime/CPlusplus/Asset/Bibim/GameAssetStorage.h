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
            BBGameModuleClass('G', 'A', 'S', 'T');
            public:
                typedef std::map<String, GameAsset*> AssetTable;
                typedef std::vector<AssetProvider*> ProviderCollection;

            public:
                GameAssetStorage();
                GameAssetStorage(GameModuleTree* modules);
                virtual ~GameAssetStorage();

                GameAsset* Load(const String& name);

                inline GameModuleTree* GetModules() const;
                inline void SetModules(GameModuleTree* value);

                inline const AssetTable& GetAssets() const;
                inline const ProviderCollection& GetProviders() const;

            private:
                void Add(AssetProvider* item); // call in AssetProvider
                void Remove(AssetProvider* item); // call in AssetProvider

            private:
                GameModuleTree* modules;
                AssetTable assets;
                ProviderCollection providers;

                friend class AssetProvider;
        };
    }

#   include <Bibim/GameAssetStorage.inl>

#endif