#pragma once
#ifndef __BIBIM_MOUSE_H__
#define __BIBIM_MOUSE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/Point.h>

    namespace Bibim
    {
        class Mouse : public GameComponent
        {
            BBClassFOURCC('M', 'O', 'U', 'S');
            public:
                Mouse();
                Mouse(Window* window);
                virtual ~Mouse();

                const MouseState& GetState();

                void SetPosition(Point value);

                Window* GetWindow();
                void SetWindow(Window* value);
                
            private:
                void OnMouseWheel(int delta);

            private:
                Window* window;
                MouseState* state;
        };
    }

#endif