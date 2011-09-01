namespace Bibim
{
    Point UIMouseEventArgs::GetPosition() const
    {
        return position;
    }

    bool UIMouseEventArgs::IsLeftButtonPressed() const
    {
        return isLeftButtonPressed;
    }

    bool UIMouseEventArgs::IsRightButtonPressed() const
    {
        return isRightButtonPressed;
    }

    bool UIMouseEventArgs::IsMiddleButtonPressed() const
    {
        return isMiddleButtonPressed;
    }
}