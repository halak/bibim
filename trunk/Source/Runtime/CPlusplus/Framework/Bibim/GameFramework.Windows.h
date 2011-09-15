#pragma once
#ifndef __BIBIM_GAMEFRAMEWORK_WINDOWS_H__
#define __BIBIM_GAMEFRAMEWORK_WINDOWS_H__

#   include <Bibim/FWD.h>
#   include <deque>

#   if (defined(BIBIM_PLATFORM_WINDOWS))

        namespace Bibim
        {
            class GameFramework
            {
                public:
                    virtual ~GameFramework();

                    void Run();

                    inline GameModuleTree* GetModules() const;
                    inline GameWindow*     GetWindow() const;
                    inline GraphicsDevice* GetGraphicsDevice() const;
                    inline Timeline*       GetMainTimeline() const;

                    inline bool GetFixedTimeStep() const;
                           void SetFixedTimeStep(bool value);

                    inline float GetFixedElapsedTime() const;
                           void  SetFixedElapsedTime(float value);

                    inline float GetMaxTimeInOneFrame() const;
                           void  SetMaxTimeInOneFrame(float value);

                    float GetFPS() const;

                protected:
                    GameFramework();

                    virtual void Initialize();
                    virtual void Finalize();

                    virtual void Update(float dt, uint timestamp);
                    virtual void Draw();

                    virtual void BeginDraw();
                    virtual void EndDraw();

                private:
                    GameModuleTree* modules;
                    GameWindow* window;
                    GraphicsDevice* graphicsDevice;
                    Timeline* mainTimeline;

                    bool  fixedTimeStep;
                    float fixedElapsedTime;
                    float maxTimeInOneFrame;
                    uint  desiredFPS;
                    std::deque<float> timestamps;
            };
        }

#       include <Bibim/GameFramework.Windows.inl>

#   endif

#endif