#pragma once
#ifndef __BIBIM_GAMECOMPONENTFACTORY_H__
#define __BIBIM_GAMECOMPONENTFACTORY_H__

#    include <Bibim/FWD.h>

    namespace Bibim
    {
        class GameComponentFactory
        {
            BBThisIsStaticClass(GameComponentFactory);
            public:
                typedef GameComponent* (*CreateFunction)();

            public:
                static GameComponent* Create(uint32 id);

                template <typename T> static void AddEntry();
                static void AddEntry(uint32 id, CreateFunction function);
                static void SortEntries();
        };
    }

#    include <Bibim/GameComponentFactory.inl>

#endif