#pragma once
#ifndef __BIBIM_GAMEASSETFACTORY_H__
#define __BIBIM_GAMEASSETFACTORY_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>

    namespace Bibim
    {
        class GameAssetFactory
        {
            BBThisIsStaticClass(GameAssetFactory);
            public:
                typedef GameAsset::StreamReader StreamReader;
                typedef GameAsset* (*CreateFunction)(StreamReader&, GameAsset*);

            public:
                static inline GameAsset* Create(StreamReader& reader);
                static GameAsset* Create(StreamReader& reader, GameAsset* existingInstance);

                template <typename T> static void AddEntry();
                static void AddEntry(int id, CreateFunction function);
                static void SortEntries();
        };
    }

#    include <Bibim/GameAssetFactory.inl>

#endif