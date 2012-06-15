namespace Bibim
{
    int UIElement::GetID() const
    {
        return id;
    }

    void UIElement::SetID(int value)
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

    void UIElement::SetNameByChars(const char* value)
    {
        if (value)
            SetName(value);
    }
}