namespace Bibim
{
    uint UIElement::GetID() const
    {
        return id;
    }

    void UIElement::SetID(uint value)
    {
        id = value;
    }

    const String& UIElement::GetName() const
    {
        return name;
    }

    void UIElement::SetName(const String& value)
    {
        name = value;
    }
}