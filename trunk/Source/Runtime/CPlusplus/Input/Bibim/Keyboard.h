#pragma once
#ifndef __BIBIM_KEYBOARD_H__
#define __BIBIM_KEYBOARD_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Key.h>
#   include <Bibim/KeyboardState.h>
#   include <Bibim/Window.h>

    namespace Bibim
    {
        class Keyboard : public GameModule, public Window::KeyboardEventListener
        {
            BBModuleClass(Keyboard, GameModule, 'K', 'B', 'D', '_');
            public:
                Keyboard();
                Keyboard(Window* window);
                virtual ~Keyboard();

                inline bool GetAllowKey(Key::Code code) const;
                inline void SetAllowKey(Key::Code code, bool allow);

                inline const KeyboardState& GetState() const;

                inline Window* GetWindow() const;
                void SetWindow(Window* value);

            private:
                void AllowDefaultKeys();

                virtual void OnKeyDown(Window* window, Key::Code code);
                virtual void OnKeyUp(Window* window, Key::Code code);

            private:
                Window* window;
                KeyboardState state;
                int allowedKeys[Key::Count / (sizeof(int) * 8)];
        };
    }

#endif