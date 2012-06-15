namespace Bibim
{
    UIDomain* UIMouseEventDispatcher::GetDomain() const
    {
        return domain;
    }

    Mouse* UIMouseEventDispatcher::GetDevice() const
    {
        return device;
    }

    UIRenderer* UIMouseEventDispatcher::GetRenderer() const
    {
        return renderer;
    }

    void UIMouseEventDispatcher::SetRenderer(UIRenderer* value)
    {
        renderer = value;
    }
}