#pragma once
#ifndef __BIBIM_GAMEFRAMEWORK_ANDROID_H__
#define __BIBIM_GAMEFRAMEWORK_ANDROID_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameFrameworkBase.h>
#   include <Bibim/String.h>
#   include <deque>

    namespace Bibim
    {
        class GameFramework : public GameFrameworkBase
        {
            BBThisIsNoncopyableClass(GameFramework);
            public:
                virtual ~GameFramework();
    
                void Run();
    
            protected:
                GameFramework();
                GameFramework(int resolutionWidth, int resolutionHeight);
    
                void Construct(int resolutionWidth, int resolutionHeight);
        };
    }

#   include <Bibim/GameFramework.Android.inl>

#endif