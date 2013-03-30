namespace Bibim
{
    Point2 UIMouseEventArgs::GetPosition() const
    {
        return position;
    }

    int UIMouseEventArgs::GetPositionX() const
    {
        return position.X;
    }

    int UIMouseEventArgs::GetPositionY() const
    {
        return position.Y;
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