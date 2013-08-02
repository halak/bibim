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
                MPQAssetProvider(GameAssetStorage* storage, MPQ* mpq);
                virtual ~MPQAssetProvider();

                virtual Stream* Open(const String& name);
                virtual bool Preload(const String& name);
                virtual GameAsset* Load(const String& name);
                virtual bool Restore(const String& name, GameAsset* asset);

                inline MPQ* GetMPQ() const;
                void SetMPQ(MPQ* value);

            private:
                static Stream* OpenActually(MPQ* mpq, const String& name);
                static GameAsset* LoadActually(GameAssetStorage* storage,
                                               MPQ* mpq,
                                               const String& name,
                                               bool isPriority);

            private:
                MPQPtr mpq;

            private:
                friend class MPQAssetPreloadingTask;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        MPQ* MPQAssetProvider::GetMPQ() const
        {
            return mpq;
        }
    }

#endif