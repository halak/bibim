#pragma once
#ifndef __BIBIM_ASSETPROVIDER_H__
#define __BIBIM_ASSETPROVIDER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class AssetProvider : public GameModule
        {
            BBGameModuleClass('A', 'S', 'P', 'V');
            public:
                AssetProvider();
                AssetProvider(GameAssetStorage* storage);
                virtual ~AssetProvider();

                virtual bool Preload(const String& name) = 0;
                virtual GameAsset* Load(const String& name) = 0;

                inline GameAssetStorage* GetStorage() const;
                void SetStorage(GameAssetStorage* value);

            protected:
                void Add(AssetPreloadingTask* item);

            private:
                GameAssetStorage* storage;
        };
    }

#   include <Bibim/AssetProvider.inl>

#endif