#pragma once
#ifndef __BIBIM_MOUSESTATE_H__
#define __BIBIM_MOUSESTATE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Point2.h>

    namespace Bibim
    {
        struct MouseState
        {
            Point2 Position;
            int Wheel;
            bool IsLeftButtonPressed;
            bool IsRightButtonPressed;
            bool IsMiddleButtonPressed;
            bool IsVisible;

            inline MouseState();
            inline MouseState(Point2 position, int wheel, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed, bool isVisible);
            inline MouseState(const MouseState& original);

            inline MouseState& operator = (const MouseState& right);
            inline bool operator == (const MouseState& right) const;
            inline bool operator != (const MouseState& right) const;

            static const MouseState Empty;
        };
    }

#   include <Bibim/MouseState.inl>

#endif