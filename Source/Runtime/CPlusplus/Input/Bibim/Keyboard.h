#pragma once
#ifndef __BIBIM_KEYBOARD_H__
#define __BIBIM_KEYBOARD_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Key.h>
#   include <Bibim/KeyboardState.h>

    namespace Bibim
    {
        class Keyboard : public GameModule
        {
            BBModuleClass(Keyboard, GameModule, 'K', 'B', 'D', '_');
            public:
                Keyboard();
                Keyboard(Window* window);
                virtual ~Keyboard();

                inline bool GetAllowKey(Key::Code code) const;
                inline void SetAllowKey(Key::Code code, bool allow);

                const KeyboardState& GetState();

                inline Window* GetWindow() const;
                inline void SetWindow(Window* value);

            private:
                void AllowDefaultKeys();

            private:
                Window* window;
                KeyboardState state;
                int allowedKeys[Key::Count / (sizeof(int) * 8)];
        };
    }

#   include <Bibim/Keyboard.inl>

#endif