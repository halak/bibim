namespace Bibim
{
    UIWindow* UICheckBox::GetCheckedNormalWindow() const
    {
        return checkedNormalWindow;
    }

    UIWindow* UICheckBox::GetCheckedPushedWindow() const
    {
        return checkedPushedWindow;
    }

    UIWindow* UICheckBox::GetCheckedHoveringWindow() const
    {
        return checkedHoveringWindow;
    }

    bool UICheckBox::GetChecked() const
    {
        return checked;
    }
}