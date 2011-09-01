namespace Bibim
{
    const String& UIElement::GetName() const
    {
        return name;
    }

    void UIElement::SetName(const String& value)
    {
        name = value;
    }
}