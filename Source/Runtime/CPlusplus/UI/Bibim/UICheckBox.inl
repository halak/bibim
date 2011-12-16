namespace Bibim
{
    UIVisual* UICheckBox::GetCheckedNormal() const
    {
        return checkedNormalVisual;
    }

    UIVisual* UICheckBox::GetCheckedPushed() const
    {
        return checkedPushedVisual;
    }

    UIVisual* UICheckBox::GetCheckedHovering() const
    {
        return checkedHoveringVisual;
    }

    bool UICheckBox::GetChecked() const
    {
        return checked;
    }
}