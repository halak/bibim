#pragma once
#ifndef __BIBIM_FILEASSETPROVIDER_H__
#define __BIBIM_FILEASSETPROVIDER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/AssetProvider.h>

    namespace Bibim
    {
        class FileAssetProvider : public AssetProvider
        {
            BBGameModuleClass('F', 'A', 'S', 'P');
            public:
                FileAssetProvider();
                virtual ~FileAssetProvider();

                virtual GameAsset* Load(const String& name);

            private:
        };
    }

#   include <Bibim/FileAssetProvider.inl>

#endif