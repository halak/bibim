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
    }

#endif