#pragma once
#ifndef __BIBIM_MOUSE_H__
#define __BIBIM_MOUSE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/MouseState.h>
#   include <Bibim/Point.h>

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

                void SetPosition(Point value);

                inline Window* GetWindow();
                inline void SetWindow(Window* value);

            private:
                Window* window;
                MouseState state;
        };
    }

#   include <Bibim/Mouse.inl>

#endif