#pragma once
#ifndef __BIBIM_GAMECOMPONENTFACTORY_H__
#define __BIBIM_GAMECOMPONENTFACTORY_H__

#   include <Bibim/FWD.h>
#   include <Bibim/UIElement.h>

    namespace Bibim
    {
        class GameComponentFactory
        {
            BBThisIsStaticClass(GameComponentFactory);
            public:
                typedef GameComponent* (*CreateFunction)();

            public:
                static GameComponent* Create(int id);

                template <typename T> static void AddEntry();
                template <typename T> static void AddSingletonEntry();
                static void AddEntry(int id, CreateFunction function);
                static void SortEntries();
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename T> void GameComponentFactory::AddEntry()
        {
            struct New
            {
                static GameComponent* Do()
                {
                    return new T();
                }
            };

            AddEntry(T::ClassID, &New::Do);
        }

        template <typename T> void GameComponentFactory::AddSingletonEntry()
        {
            struct Get
            {
                static GameComponent* Do()
                {
                    return T::Instance;
                }
            };

            AddEntry(T::ClassID, &Get::Do);
        }
    }

#endif