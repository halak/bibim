#pragma once
#ifndef __BIBIM_GAMEFRAMEWORK_BASE_H__
#define __BIBIM_GAMEFRAMEWORK_BASE_H__

#include <Bibim/FWD.h>
#include <Bibim/String.h>
#include <deque>

namespace Bibim
{
    class GameFrameworkBase
    {
        BBThisIsNoncopyableClass(GameFrameworkBase);
        public:
            virtual ~GameFrameworkBase();

            void Exit();

            inline GameModuleTree* GetModules() const;
            inline GameWindow*     GetWindow() const;
            inline GraphicsDevice* GetGraphicsDevice() const;
            inline Timeline*       GetMainTimeline() const;

            inline const String& GetStartupArgs() const;

            inline bool GetFixedTimeStep() const;
                   void SetFixedTimeStep(bool value);

            inline float GetFixedElapsedTime() const;
                   void  SetFixedElapsedTime(float value);

            inline float GetMaxTimeInOneFrame() const;
                   void  SetMaxTimeInOneFrame(float value);

            float GetFPS() const;

        protected:
            GameFrameworkBase();

            void Construct(int width, int height, const String& startupArgs);

            virtual void Initialize();
            virtual void Finalize();

            void PostInitialize();
            
            void StepFrame();
            void UpdateFrame();
            void DrawFrame();

            virtual void Update(float dt, int timestamp);
            virtual void Draw();

            virtual bool BeginDraw();
            virtual void EndDraw();

        private:
            GameModuleTree* modules;
            GameWindow* window;
            GraphicsDevice* graphicsDevice;
            Timeline* mainTimeline;
            String startupArgs;

            bool  fixedTimeStep;
            float fixedElapsedTime;
            float maxTimeInOneFrame;
            int  desiredFPS;
            int  timestamp;
            std::deque<float> timestamps;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    GameModuleTree* GameFrameworkBase::GetModules() const
    {
        return modules;
    }

    GameWindow* GameFrameworkBase::GetWindow() const
    {
        return window;
    }

    GraphicsDevice* GameFrameworkBase::GetGraphicsDevice() const
    {
        return graphicsDevice;
    }

    Timeline* GameFrameworkBase::GetMainTimeline() const
    {
        return mainTimeline;
    }

    const String& GameFrameworkBase::GetStartupArgs() const
    {
        return startupArgs;
    }

    bool GameFrameworkBase::GetFixedTimeStep() const
    {
        return fixedTimeStep;
    }

    float GameFrameworkBase::GetFixedElapsedTime() const
    {
        return fixedElapsedTime;
    }

    float GameFrameworkBase::GetMaxTimeInOneFrame() const
    {
        return maxTimeInOneFrame;
    }
}

#endif