#pragma once
#ifndef __BIBIM_KEYBOARD_H__
#define __BIBIM_KEYBOARD_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameComponent.h>
#   include <Bibim/Key.h>

    namespace Bibim
    {
        class Keyboard : public GameComponent
        {
            BBClassFOURCC('K', 'B', 'D', '_');
            public:
                Keyboard();
                Keyboard(Window* window);
                virtual ~Keyboard();

                inline bool GetAllowKey(Key::Code code) const;
                inline void SetAllowKey(Key::Code code, bool allow);

                const KeyboardState& GetState();

                Window* GetWindow() const;
                void SetWindow(Window* value);

            private:
                void AllowDefaultKeys();

            private:
                Window* window;
                KeyboardState* state;
                dword allowedKeys[Key::Count / (sizeof(dword) * 8)];
        };
    }

#   include <Bibim/Keyboard.inl>

#endif