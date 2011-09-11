#pragma once
#ifndef __BIBIM_GAMEMODULEFACTORY_H__
#define __BIBIM_GAMEMODULEFACTORY_H__

#    include <Bibim/FWD.h>

    namespace Bibim
    {
        class GameModuleFactory
        {
            BBThisIsStaticClass(GameModuleFactory);
            public:
                typedef GameModule* (*CreateFunction)();

            public:
                static GameModule* Create(uint32 id);

                template <typename T> static void AddEntry();
                static void AddEntry(uint32 id, CreateFunction function);
                static void SortEntries();
        };
    }

#    include <Bibim/GameModuleFactory.inl>

#endif