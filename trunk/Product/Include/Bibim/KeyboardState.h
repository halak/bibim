#pragma once
#ifndef __BIBIM_KEYBOARDSTATE_H__
#define __BIBIM_KEYBOARDSTATE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Key.h>

    namespace Bibim
    {
        struct KeyboardState
        {
            int Keys[Key::Count / (sizeof(int) * 8)];

            inline KeyboardState();
            inline KeyboardState(const KeyboardState& original);

            inline bool IsPressed() const;
            inline bool IsPressed(Key::Code code) const;
            inline bool IsReleased(Key::Code code) const;

            inline KeyboardState& operator = (const KeyboardState& right);
            inline bool operator == (const KeyboardState& right) const;
            inline bool operator != (const KeyboardState& right) const;

            static const KeyboardState Empty;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        KeyboardState::KeyboardState()
        {
            for (int i = 0; i < sizeof(Keys) / sizeof(Keys[0]); i++)
                Keys[i] = 0x00000000;
        }

        KeyboardState::KeyboardState(const KeyboardState& original)
        {
            for (int i = 0; i < sizeof(Keys) / sizeof(Keys[0]); i++)
                Keys[i] = original.Keys[i];
        }

        bool KeyboardState::IsPressed() const
        {
            for (int i = 0; i < sizeof(Keys) / sizeof(Keys[0]); i++)
            {
                if (Keys[i] != 0x00000000)
                    return true;
            }

            return false;
        }

        bool KeyboardState::IsPressed(Key::Code code) const
        {
            const int index = static_cast<int>(static_cast<int>(code) / (sizeof(int) * 8));
            const int bit   = static_cast<int>(static_cast<int>(code) % (sizeof(int) * 8));
            return Keys[index] & (0x80000000 >> bit) ? true : false;
        }

        bool KeyboardState::IsReleased(Key::Code code) const
        {
            return !IsPressed(code);
        }

        KeyboardState& KeyboardState::operator = (const KeyboardState& right)
        {
            for (int i = 0; i < sizeof(Keys) / sizeof(Keys[0]); i++)
                Keys[i] = right.Keys[i];

            return *this;
        }

        bool KeyboardState::operator == (const KeyboardState& right) const
        {
            for (int i = 0; i < sizeof(Keys) / sizeof(Keys[0]); i++)
            {
                if (Keys[i] != right.Keys[i])
                    return false;
            }

            return true;
        }

        bool KeyboardState::operator != (const KeyboardState& right) const
        {
            return !operator == (right);
        }
    }

#endif