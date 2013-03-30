#pragma once
#ifndef __BIBIM_MOUSE_H__
#define __BIBIM_MOUSE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/MouseState.h>
#   include <Bibim/Point2.h>
#   include <Bibim/Window.h>

    namespace Bibim
    {
        class Mouse : public GameModule, public Window::MouseEventListener
        {
            BBModuleClass(Mouse, GameModule, 'M', 'O', 'U', 'S');
            public:
                Mouse();
                Mouse(Window* window);
                virtual ~Mouse();

                inline const MouseState& GetState();

                inline void Show();
                inline void Hide();

                void SetPosition(Point2 value);
                void SetVisible(bool value);

                inline Window* GetWindow();
                void SetWindow(Window* value);

            private:
                virtual void OnMouseMove(Window* window, int x, int y);
                virtual void OnMouseLeftButtonDown(Window* window, int x, int y);
                virtual void OnMouseLeftButtonUp(Window* window, int x, int y);
                virtual void OnMouseMiddleButtonDown(Window* window, int x, int y);
                virtual void OnMouseMiddleButtonUp(Window* window, int x, int y);
                virtual void OnMouseRightButtonDown(Window* window, int x, int y);
                virtual void OnMouseRightButtonUp(Window* window, int x, int y);
                virtual void OnMouseWheel(Window* window, int value);

            private:
                Window* window;
                MouseState state;
                bool isVisible;
        };
    }

#   include <Bibim/Mouse.inl>

#endif