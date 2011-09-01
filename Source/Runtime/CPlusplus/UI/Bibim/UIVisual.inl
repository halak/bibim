namespace Bibim
{
    void UIVisual::Show()
    {
        SetShown(true);
    }

    void UIVisual::Hide()
    {
        SetShown(false);
    }

    float UIVisual::GetOpacity() const
    {
        return opacity;
    }

    bool UIVisual::GetShown() const
    {
        return shown;
    }

    void UIVisual::SetShown(bool value)
    {
        shown = value;
    }

    UIFrame* UIVisual::GetFrame() const
    {
        return frame;
    }

    UITransform* UIVisual::GetTransform() const
    {
        return transform;
    }

    UIEventMap* UIVisual::GetEventMap() const
    {
        return eventMap;
    }

    Vector2 UIVisual::GetDesiredSize()
    {
        return Vector2(-1.0f, -1.0f);
    }

    UIPanel* UIVisual::GetParent() const
    {
        return parent;
    }
    
    bool UIVisual::IsVisible() const
    {
        return GetShown() && GetOpacity() > 0.0f;
    }
}