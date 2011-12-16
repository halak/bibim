namespace Bibim
{
    void UIVisual::Show()
    {
        SetVisibility(Visible);
    }

    void UIVisual::Hide()
    {
        SetVisibility(Collasped);
    }

    void UIVisual::SetBounds(float x, float y, float width, float height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    void UIVisual::SetAbsoluteBounds(int x, int y, int width, int height)
    {
        SetAbsoluteBounds(static_cast<float>(x),
                          static_cast<float>(y),
                          static_cast<float>(width),
                          static_cast<float>(height));
    }

    void UIVisual::SetAbsoluteBounds(float x, float y, float width, float height)
    {
        SetBounds(x, y, width, height);
        xMode = AbsolutePosition;
        yMode = AbsolutePosition;
        widthMode  = AbsoluteSize;
        heightMode = AbsoluteSize;
    }

    void UIVisual::SetRelativeBounds(float x, float y, float width, float height)
    {
        SetBounds(x, y, width, height);
        xMode = RelativePosition;
        yMode = RelativePosition;
        widthMode  = RelativeSize;
        heightMode = RelativeSize;
    }

    float UIVisual::GetX() const
    {
        return x;
    }

    void UIVisual::SetX(float value)
    {
        x = value;
    }

    float UIVisual::GetY() const
    {
        return y;
    }

    void UIVisual::SetY(float value)
    {
        y = value;
    }

    float UIVisual::GetWidth() const
    {
        return width;
    }

    void UIVisual::SetWidth(float value)
    {
        width = value > 0.0f ? value : 0.0f;
    }

    float UIVisual::GetHeight() const
    {
        return height;
    }

    void UIVisual::SetHeight(float value)
    {
        height = value > 0.0f ? value : 0.0f;
    }

    UIVisual::PositionMode UIVisual::GetXMode() const
    {
        return static_cast<PositionMode>(xMode);
    }

    void UIVisual::SetXMode(PositionMode value)
    {
        xMode = static_cast<byte>(value);
    }

    UIVisual::PositionMode UIVisual::GetYMode() const
    {
        return static_cast<PositionMode>(yMode);
    }

    void UIVisual::SetYMode(PositionMode value)
    {
        yMode = static_cast<byte>(value);
    }

    UIVisual::SizeMode UIVisual::GetWidthMode() const
    {
        return static_cast<SizeMode>(widthMode);
    }

    void UIVisual::SetWidthMode(SizeMode value)
    {
        widthMode = static_cast<byte>(value);
    }

    UIVisual::SizeMode UIVisual::GetHeightMode() const
    {
        return static_cast<SizeMode>(heightMode);
    }

    void UIVisual::SetHeightMode(SizeMode value)
    {
        heightMode = static_cast<byte>(value);
    }

    UIVisual::AnchorPoint UIVisual::GetAlignment() const
    {
        return static_cast<AnchorPoint>(alignment);
    }

    void UIVisual::SetAlignment(AnchorPoint value)
    {
        alignment = static_cast<byte>(value);
    }

    float UIVisual::GetOpacity() const
    {
        return static_cast<float>(opacity) / 255.0f;
    }

    UIVisual::Visibility UIVisual::GetVisibility() const
    {
        return static_cast<Visibility>(visibility);
    }

    void UIVisual::SetVisibility(Visibility value)
    {
        visibility = static_cast<byte>(value);
    }

    int UIVisual::GetZOrder() const
    {
        return static_cast<int>(zOrder);
    }

    UIEventMap* UIVisual::GetEventMap() const
    {
        return eventMap;
    }

    UIEffectMap* UIVisual::GetEffectMap() const
    {
        return effectMap;
    }

    UIPanel* UIVisual::GetParent() const
    {
        return parent;
    }
    
    bool UIVisual::IsVisible() const
    {
        return GetVisibility() == Visible && GetOpacity() > 0.0f;
    }
}