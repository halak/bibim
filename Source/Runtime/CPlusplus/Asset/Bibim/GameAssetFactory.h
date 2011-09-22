#pragma once
#ifndef __BIBIM_GAMEASSETFACTORY_H__
#define __BIBIM_GAMEASSETFACTORY_H__

#    include <Bibim/FWD.h>

    namespace Bibim
    {
        class GameAssetFactory
        {
            BBThisIsStaticClass(GameAssetFactory);
            public:
                typedef GameAsset* (*CreateFunction)(AssetStreamReader&, GameAsset*);

            public:
                static inline GameAsset* Create(AssetStreamReader& reader);
                static GameAsset* Create(AssetStreamReader& reader, GameAsset* existingInstance);

                template <typename T> static void AddEntry();
                static void AddEntry(uint32 id, CreateFunction function);
                static void SortEntries();
        };
    }

#    include <Bibim/GameAssetFactory.inl>

#endif