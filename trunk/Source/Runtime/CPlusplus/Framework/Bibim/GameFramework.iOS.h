#pragma once
#ifndef __BIBIM_GAMEFRAMEWORK_IOS_H__
#define __BIBIM_GAMEFRAMEWORK_IOS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameFrameworkBase.h>

    namespace Bibim
    {
        class GameFramework : public GameFrameworkBase
        {
            BBThisIsNoncopyableClass(GameFramework);
            public:
                virtual ~GameFramework();

                void init();
                void update();
                void draw();

                inline IME* GetIME() const;

            protected:
                GameFramework();
                GameFramework(int width, int height);
    
                void Construct(int width, int height);

            private:
                IME* ime;

            public:
                static GameFramework* Create();
                static GameFramework* SingletonInstance;
        };
    }

#   include <Bibim/GameFramework.iOS.inl>

#endif