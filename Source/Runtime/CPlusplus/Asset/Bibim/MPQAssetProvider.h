#pragma once
#ifndef __BIBIM_MPQASSETPROVIDER_H__
#define __BIBIM_MPQASSETPROVIDER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/AssetProvider.h>

    namespace Bibim
    {
        class MPQAssetPreloadingTask;
        class MPQAssetProvider : public AssetProvider
        {
            BBModuleClass(MPQAssetProvider, AssetProvider, 'F', 'A', 'S', 'P');
            public:
                MPQAssetProvider();
                MPQAssetProvider(GameAssetStorage* storage);
                MPQAssetProvider(GameAssetStorage* storage, const String& directory);
                virtual ~MPQAssetProvider();

                virtual bool Preload(const String& name);
                virtual GameAsset* Load(const String& name);

                inline const String& GetDirectory() const;
                void SetDirectory(const String& value);

            private:
                static GameAsset* LoadActually(GameAssetStorage* storage,
                                               const String& directory,
                                               const String& name,
                                               bool isPriority);

            private:
                String directory;

            private:
                friend class MPQAssetPreloadingTask;
        };
    }

#   include <Bibim/MPQAssetProvider.inl>

#endif