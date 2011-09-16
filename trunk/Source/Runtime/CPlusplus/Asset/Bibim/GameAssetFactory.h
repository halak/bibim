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
                typedef GameAsset* (*CreateFunction)(AssetReader&, GameAsset*);

            public:
                static inline GameAsset* Create(AssetReader& reader);
                static GameAsset* Create(AssetReader& reader, GameAsset* existingInstance);

                template <typename T> static void AddEntry();
                static void AddEntry(uint32 id, CreateFunction function);
                static void SortEntries();
        };
    }

#    include <Bibim/GameAssetFactory.inl>

#endif