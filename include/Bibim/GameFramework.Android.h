#pragma once
#ifndef __BIBIM_GAMEFRAMEWORK_ANDROID_H__
#define __BIBIM_GAMEFRAMEWORK_ANDROID_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_PLATFORM_ANDROID))

#include <Bibim/GameFrameworkBase.h>

namespace Bibim
{
    class GameFramework : public GameFrameworkBase
    {
        BBThisIsNoncopyableClass(GameFramework);
        public:
            virtual ~GameFramework();

            virtual void Exit();

            void init();
            void step();

            inline IME* GetIME() const;

            static void PlayBGM(const String& path);
            static void SetBGMVolume(float value);
            static void PlaySFX(const String& path, int group);
            static void SetSFXVolume(float value);

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

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    IME* GameFramework::GetIME() const
    {
        return ime;
    }
}

#endif
#endif