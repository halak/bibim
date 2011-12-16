namespace Bibim
{
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
}