namespace Bibim
{
    void UIButton::Freeze()
    {
        SetFrozen(true);
    }

    void UIButton::Unfreeze()
    {
        SetFrozen(false);
    }

    UIButton::State UIButton::GetCurrentState() const
    {
        return currentState;
    }

    UIVisual* UIButton::GetNormal() const
    {
        return normalVisual;
    }

    UIVisual* UIButton::GetPushed() const
    {
        return pushedVisual;
    }

    UIVisual* UIButton::GetHovering() const
    {
        return hoveringVisual;
    }

    UIVisual* UIButton::GetCurrent() const
    {
        return currentVisual;
    }

    bool UIButton::GetHideInactives() const
    {
        return hideInactives;
    }

    bool UIButton::GetFocusVisible() const
    {
        return focusVisible;
    }

    bool UIButton::GetFrozen() const
    {
        return frozen;
    }
}