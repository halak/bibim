#pragma once
#ifndef __BIBIM_GAMEFRAMEWORK_EMSCRIPTEN_H__
#define __BIBIM_GAMEFRAMEWORK_EMSCRIPTEN_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_PLATFORM_EMSCRIPTEN))

#include <Bibim/GameFrameworkBase.h>

namespace Bibim
{
    class GameFramework : public GameFrameworkBase
    {
        BBThisIsNoncopyableClass(GameFramework);
        public:
            virtual ~GameFramework();

            void init();

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
            static void DoStep();
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    IME* GameFramework::GetIME() const
    {
        return ime;
    }
}

#endif
#endif