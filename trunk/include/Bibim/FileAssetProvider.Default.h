#pragma once
#ifndef __BIBIM_FILEASSETPROVIDER_DEFAULT_H__
#define __BIBIM_FILEASSETPROVIDER_DEFAULT_H__

#include <Bibim/FWD.h>
#include <Bibim/FileAssetProviderBase.h>

namespace Bibim
{
    class FileAssetProvider : public FileAssetProviderBase
    {
        BBModuleClass(FileAssetProvider, FileAssetProviderBase, 'F', 'A', 'S', 'P');
        public:
            FileAssetProvider();
            FileAssetProvider(GameAssetStorage* storage);
            FileAssetProvider(GameAssetStorage* storage, const String& directory);
            virtual ~FileAssetProvider();
    };
}

#endif