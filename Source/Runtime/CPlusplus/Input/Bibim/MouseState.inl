namespace Bibim
{
    MouseState::MouseState()
        : Position(Point2::Zero),
          Wheel(0),
          IsLeftButtonPressed(false),
          IsRightButtonPressed(false),
          IsMiddleButtonPressed(false)
    {
    }

    MouseState::MouseState(Point2 position, int wheel, bool isLeftButtonPressed, bool isRightButtonPressed, bool isMiddleButtonPressed)
        : Position(position),
          Wheel(wheel),
          IsLeftButtonPressed(isLeftButtonPressed),
          IsRightButtonPressed(isRightButtonPressed),
          IsMiddleButtonPressed(isMiddleButtonPressed)
    {
    }

    MouseState::MouseState(const MouseState& original)
        : Position(original.Position),
          Wheel(original.Wheel),
          IsLeftButtonPressed(original.IsLeftButtonPressed),
          IsRightButtonPressed(original.IsRightButtonPressed),
          IsMiddleButtonPressed(original.IsMiddleButtonPressed)
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
        return *this;
    }

    bool MouseState::operator == (const MouseState& right) const
    {
        return Position == right.Position &&
               Wheel == right.Wheel &&
               IsLeftButtonPressed == right.IsLeftButtonPressed &&
               IsRightButtonPressed == right.IsRightButtonPressed &&
               IsMiddleButtonPressed == right.IsMiddleButtonPressed;
    }

    bool MouseState::operator != (const MouseState& right) const
    {
        return !operator == (right);
    }
}