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

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        MouseState::MouseState()
            : Position(Point2::Zero),
              Wheel(0),
              IsLeftButtonPressed(false),
              IsRightButtonPressed(false),
              IsMiddleButtonPressed(false),
              IsVisible(true)
        {
        }

        MouseState::MouseState(Point2 position, int wheel, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed, bool isVisible)
            : Position(position),
              Wheel(wheel),
              IsLeftButtonPressed(isLeftButtonPressed),
              IsRightButtonPressed(isRightButtonPressed),
              IsMiddleButtonPressed(isMiddleButtonPressed),
              IsVisible(isVisible)
        {
        }

        MouseState::MouseState(const MouseState& original)
            : Position(original.Position),
              Wheel(original.Wheel),
              IsLeftButtonPressed(original.IsLeftButtonPressed),
              IsRightButtonPressed(original.IsRightButtonPressed),
              IsMiddleButtonPressed(original.IsMiddleButtonPressed),
              IsVisible(original.IsVisible)
        {
        }

        MouseState& MouseState::operator = (const MouseState& right)
        {
            if (this == &right)
                return *this;

            Position = right.Position;
            Wheel = right.Wheel;
            IsLeftButtonPressed = right.IsLeftButtonPressed;
            IsRightButtonPressed = right.IsRightButtonPressed;
            IsMiddleButtonPressed = right.IsMiddleButtonPressed;
            IsVisible = right.IsVisible;
            return *this;
        }

        bool MouseState::operator == (const MouseState& right) const
        {
            return Position == right.Position &&
                   Wheel == right.Wheel &&
                   IsLeftButtonPressed == right.IsLeftButtonPressed &&
                   IsRightButtonPressed == right.IsRightButtonPressed &&
                   IsMiddleButtonPressed == right.IsMiddleButtonPressed &&
                   IsVisible == right.IsVisible;
        }

        bool MouseState::operator != (const MouseState& right) const
        {
            return !operator == (right);
        }
    }

#endif