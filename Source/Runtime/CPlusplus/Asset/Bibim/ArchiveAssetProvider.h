#pragma once
#ifndef __BIBIM_ARCHIVEASSETPROVIDER_H__
#define __BIBIM_ARCHIVEASSETPROVIDER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/AssetProvider.h>

    namespace Bibim
    {
        class ArchiveAssetProvider : public AssetProvider
        {
            BBModuleClass(ArchiveAssetProvider, AssetProvider, 'A', 'A', 'S', 'P');
            public:
                ArchiveAssetProvider();
                ArchiveAssetProvider(GameAssetStorage* storage);
                ArchiveAssetProvider(GameAssetStorage* storage, Archive* archive);
                virtual ~ArchiveAssetProvider();

                virtual bool Preload(const String& name);
                virtual GameAsset* Load(const String& name);

                inline Archive* GetArchive() const;
                void SetArchive(Archive* value);

            private:
                Archive* archive;
        };
    }

#   include <Bibim/ArchiveAssetProvider.inl>

#endif