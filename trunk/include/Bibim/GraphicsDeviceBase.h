#pragma once
#ifndef __BIBIM_GRAPHICSDEVICE_BASE_H__
#define __BIBIM_GRAPHICSDEVICE_BASE_H__

#include <Bibim/FWD.h>
#include <Bibim/GameModule.h>
#include <Bibim/Window.h>
#include <vector>

namespace Bibim
{
    class GraphicsDeviceBase : public GameModule, public Window::ResizeEventListener
    {
        BBAbstractModuleClass(GraphicsDeviceBase, GameModule);
        public:
            class LostEventListener
            {
                public:
                    virtual void OnGraphicsDeviceLost(GraphicsDeviceBase* g) = 0;
            };

            class RestoreEventListener
            {
                public:
                    virtual void OnGraphicsDeviceRestore(GraphicsDeviceBase* g) = 0;
            };

        public:
            GraphicsDeviceBase();
            virtual ~GraphicsDeviceBase();

            inline Window* GetWindow() const;
            void SetWindow(Window* value);

            void AddLostEventListener(LostEventListener* listener);
            void RemoveLostEventListener(LostEventListener* listener);

            void AddRestoreEventListener(RestoreEventListener* listener);
            void RemoveRestoreEventListener(RestoreEventListener* listener);

        protected:
            virtual void Initialize();
            virtual void Finalize();

            void Reset();

        private:
            virtual void OnWindowResized(Window* window);

        private:
            Window* window;
            std::vector<LostEventListener*> lostEventListeners;
            std::vector<RestoreEventListener*> restoreEventListeners;
            bool isReset;
            bool __padding__[3];
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Window* GraphicsDeviceBase::GetWindow() const
    {
        return window;
    }
}

#endif