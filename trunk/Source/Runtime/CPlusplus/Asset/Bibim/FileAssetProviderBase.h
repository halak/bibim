#pragma once
#ifndef __BIBIM_FILEASSETPROVIDERBASE_H__
#define __BIBIM_FILEASSETPROVIDERBASE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/AssetProvider.h>

    namespace Bibim
    {
        class FileAssetPreloadingTask;
        class FileAssetProviderBase : public AssetProvider
        {
            BBAbstractModuleClass(FileAssetProvider, AssetProvider);
            public:
                FileAssetProviderBase();
                FileAssetProviderBase(GameAssetStorage* storage);
                FileAssetProviderBase(GameAssetStorage* storage, const String& directory);
                virtual ~FileAssetProviderBase();

                virtual bool Preload(const String& name);
                virtual GameAsset* Load(const String& name);
                virtual bool Restore(const String& name, GameAsset* asset);

                inline const String& GetDirectory() const;
                void SetDirectory(const String& value);

            protected:
                virtual Stream* Open(const char* filename);

            private:
                GameAsset* LoadActually(GameAssetStorage* storage,
                                        const String& directory,
                                        const String& name,
                                        bool isPriority,
                                        GameAsset* existingInstance);

            private:
                String directory;

            private:
                friend class FileAssetPreloadingTask;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        const String& FileAssetProviderBase::GetDirectory() const
        {
            return directory;
        }
    }

#endif