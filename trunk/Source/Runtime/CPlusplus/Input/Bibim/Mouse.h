#pragma once
#ifndef __BIBIM_MOUSE_H__
#define __BIBIM_MOUSE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/MouseState.h>
#   include <Bibim/Point2.h>

    namespace Bibim
    {
        class Mouse : public GameModule
        {
            BBModuleClass(Mouse, GameModule, 'M', 'O', 'U', 'S');
            public:
                Mouse();
                Mouse(Window* window);
                virtual ~Mouse();

                const MouseState& GetState();

                inline void Show();
                inline void Hide();

                void SetPosition(Point2 value);
                void SetVisible(bool value);

                inline Window* GetWindow();
                inline void SetWindow(Window* value);

            private:
                Window* window;
                MouseState state;
                bool isVisible;
        };
    }

#   include <Bibim/Mouse.inl>

#endif