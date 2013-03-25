namespace Bibim
{
    UIEditText::Format UIEditText::GetFormat() const
    {
        return format;
    }

    bool UIEditText::GetFrozen() const
    {
        return frozen;
    }

    void UIEditText::SetFrozen(bool value)
    {
        frozen = value;
    }
}