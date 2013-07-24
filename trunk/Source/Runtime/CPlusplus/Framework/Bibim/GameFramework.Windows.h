#pragma once
#ifndef __BIBIM_GAMEFRAMEWORK_WINDOWS_H__
#define __BIBIM_GAMEFRAMEWORK_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameFrameworkBase.h>

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
                GameFramework(int width, int height);
    
                void Construct(int width, int height);
        };
    }

#endif