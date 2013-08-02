#pragma once
#ifndef __BIBIM_WINDOW_H__
#define __BIBIM_WINDOW_H__

#include <Bibim/FWD.h>
#include <Bibim/GameModule.h>
#include <Bibim/Key.h>
#include <Bibim/Point2.h>
#include <vector>

namespace Bibim
{
    class Window : public GameModule
    {
        BBAbstractModuleClass(Window, GameModule);
        public:
            class ResizeEventListener
            {
                public:
                    virtual ~ResizeEventListener() { }

                    virtual void OnWindowResized(Window* window) = 0;
            };

            class MouseEventListener
            {
                public:
                    virtual ~MouseEventListener() { }

                    virtual void OnMouseMove(Window* window, int x, int y) = 0;
                    virtual void OnMouseLeftButtonDown(Window* window, int x, int y) = 0;
                    virtual void OnMouseLeftButtonUp(Window* window, int x, int y) = 0;
                    virtual void OnMouseMiddleButtonDown(Window* window, int x, int y) = 0;
                    virtual void OnMouseMiddleButtonUp(Window* window, int x, int y) = 0;
                    virtual void OnMouseRightButtonDown(Window* window, int x, int y) = 0;
                    virtual void OnMouseRightButtonUp(Window* window, int x, int y) = 0;
                    virtual void OnMouseWheel(Window* window, int value) = 0;
            };

            class KeyboardEventListener
            {
                public:
                    virtual ~KeyboardEventListener() { }

                    virtual void OnKeyDown(Window* window, Key::Code code) = 0;
                    virtual void OnKeyUp(Window* window, Key::Code code) = 0;
            };

        public:
            virtual ~Window();

            virtual void Close() = 0;

            virtual Point2 GetPosition() const = 0;
            virtual void   SetPosition(Point2 value) = 0;

            virtual Point2 GetSize() const = 0;
            virtual void   SetSize(Point2 value) = 0;

            virtual bool GetVisible() const = 0;
            virtual void SetVisible(bool value) = 0;

            virtual void* GetHandle() const = 0;
            virtual void* GetDisplayHandle() const = 0;

            void AddResizeEventListener(ResizeEventListener* listener);
            void RemoveResizeEventListener(ResizeEventListener* listener);
            void AddMouseEventListener(MouseEventListener* listener);
            void RemoveMouseEventListener(MouseEventListener* listener);
            void AddKeyboardEventListener(KeyboardEventListener* listener);
            void RemoveKeyboardEventListener(KeyboardEventListener* listener);

        public:
            void RaiseResizedEvent();
            void RaiseMouseMoveEvent(int x, int y);
            void RaiseMouseLeftButtonDownEvent(int x, int y);
            void RaiseMouseLeftButtonUpEvent(int x, int y);
            void RaiseMouseMiddleButtonDownEvent(int x, int y);
            void RaiseMouseMiddleButtonUpEvent(int x, int y);
            void RaiseMouseRightButtonDownEvent(int x, int y);
            void RaiseMouseRightButtonUpEvent(int x, int y);
            void RaiseMouseWheelEvent(int value);
            void RaiseKeyDownEvent(Key::Code code);
            void RaiseKeyUpEvent(Key::Code code);

        protected:
            inline Window();

        private:
            std::vector<ResizeEventListener*> resizeEventListeners;
            std::vector<MouseEventListener*> mouseEventListeners;
            std::vector<KeyboardEventListener*> keyboardEventListeners;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Window::Window()
    {
    }
}

#endif