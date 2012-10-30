#pragma once
#ifndef __BIBIM_FILEASSETPROVIDER_H__
#define __BIBIM_FILEASSETPROVIDER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/AssetProvider.h>

    namespace Bibim
    {
        class FileAssetPreloadingTask;
        class FileAssetProvider : public AssetProvider
        {
            BBModuleClass(FileAssetProvider, AssetProvider, 'F', 'A', 'S', 'P');
            public:
                FileAssetProvider();
                FileAssetProvider(GameAssetStorage* storage);
                FileAssetProvider(GameAssetStorage* storage, const String& directory);
                virtual ~FileAssetProvider();

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
                friend class FileAssetPreloadingTask;
        };
    }

#   include <Bibim/FileAssetProvider.inl>

#endif