namespace Bibim
{
    UIButton::State UIButton::GetCurrentState() const
    {
        return currentState;
    }

    UIWindow* UIButton::GetNormalWindow() const
    {
        return normalWindow;
    }

    UIWindow* UIButton::GetPushedWindow() const
    {
        return pushedWindow;
    }

    UIWindow* UIButton::GetHoveringWindow() const
    {
        return hoveringWindow;
    }

    UIWindow* UIButton::GetCurrentWindow() const
    {
        return currentWindow;
    }

    bool UIButton::GetHideInactives() const
    {
        return hideInactives;
    }

    bool UIButton::GetStateSizeReferenced() const
    {
        return stateSizeReferenced;
    }

    void UIButton::SetStateSizeReferenced(bool value)
    {
        stateSizeReferenced = value;
    }
}