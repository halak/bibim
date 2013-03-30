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

    int UIElement::GetTag() const
    {
        return tag;
    }

    void UIElement::SetTag(int value)
    {
        tag = value;
    }
}