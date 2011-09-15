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
                virtual ~AssetProvider();

                virtual GameAsset* Load(const String& name) = 0;

            private:
        };
    }

#   include <Bibim/AssetProvider.inl>

#endif