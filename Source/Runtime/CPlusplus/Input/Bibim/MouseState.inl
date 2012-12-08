namespace Bibim
{
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