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

    UIPixelEffect* UIVisual::FindEffectByChars(const char* name)
    {
        if (name)
            return FindEffect(name);
        else
            return nullptr;
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

    void UIVisual::SetXY(float x, float y)
    {
        this->x = x;
        this->y = y;
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

    void UIVisual::SetSize(float width, float height)
    {
        SetWidth(width);
        SetHeight(height);
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

    void UIVisual::SetXYMode(PositionMode xyMode)
    {
        this->xMode = static_cast<byte>(xyMode);
        this->yMode = this->xMode;
    }

    void UIVisual::SetXYMode(PositionMode xMode, PositionMode yMode)
    {
        this->xMode = static_cast<byte>(xMode);
        this->yMode = static_cast<byte>(yMode);
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

    void UIVisual::SetSizeMode(SizeMode sizeMode)
    {
        this->widthMode = static_cast<byte>(sizeMode);
        this->heightMode = this->widthMode;
    }

    void UIVisual::SetSizeMode(SizeMode widthMode, SizeMode heightMode)
    {
        this->widthMode = static_cast<byte>(widthMode);
        this->heightMode = static_cast<byte>(heightMode);
    }

    Vector2 UIVisual::GetOrigin() const
    {
        return origin;
    }

    void UIVisual::SetOrigin(Vector2 value)
    {
        origin = value;
    }

    UIVisual::AnchorPoint UIVisual::GetAnchorPoint() const
    {
        return static_cast<AnchorPoint>(anchorPoint);
    }

    void UIVisual::SetAnchorPoint(AnchorPoint value)
    {
        anchorPoint = static_cast<byte>(value);
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

    bool UIVisual::GetPickable() const
    {
        return isPickable;
    }

    void UIVisual::SetPickable(bool value)
    {
        isPickable = value;
    }

    UIEventMap* UIVisual::GetEventMap() const
    {
        return eventMap;
    }

    UIEffectMap* UIVisual::GetEffectMap() const
    {
        return effectMap;
    }

    UITransform* UIVisual::GetTransform() const
    {
        return transform;
    }

    UIPanel* UIVisual::GetParent() const
    {
        return parent;
    }
    
    bool UIVisual::IsVisible() const
    {
        return GetVisibility() == Visible && GetOpacity() > 0.0f;
    }

    void UIVisual::AlignToByChars(const char* value)
    {
        AlignTo(ConvertFromStringToAnchorPoint(value));
    }

    const char* UIVisual::GetXModeAsChars() const
    {
        return ConvertFromPositionModeToString(GetXMode());
    }

    void UIVisual::SetXModeByChars(const char* value)
    {
        SetXMode(ConvertFromStringToPositionMode(value));
    }

    const char* UIVisual::GetYModeAsChars() const
    {
        return ConvertFromPositionModeToString(GetYMode());
    }

    void UIVisual::SetYModeByChars(const char* value)
    {
        SetYMode(ConvertFromStringToPositionMode(value));
    }

    void UIVisual::SetXYModeByChars(const char* xMode, const char* yMode)
    {
        if (yMode)
        {
            SetXMode(ConvertFromStringToPositionMode(xMode));
            SetYMode(ConvertFromStringToPositionMode(yMode));
        }
        else
        {
            const PositionMode mode = ConvertFromStringToPositionMode(xMode);
            SetXMode(mode);
            SetYMode(mode);
        }
    }

    const char* UIVisual::GetWidthModeAsChars() const
    {
        return ConvertFromSizeModeToString(GetWidthMode());
    }

    void UIVisual::SetWidthModeByChars(const char* value)
    {
        SetWidthMode(ConvertFromStringToSizeMode(value));
    }

    const char* UIVisual::GetHeightModeAsChars() const
    {
        return ConvertFromSizeModeToString(GetHeightMode());
    }

    void UIVisual::SetHeightModeByChars(const char* value)
    {
        SetHeightMode(ConvertFromStringToSizeMode(value));
    }

    void UIVisual::SetSizeModeByChars(const char* widthMode, const char* heightMode)
    {
        if (heightMode)
        {
            SetWidthMode(ConvertFromStringToSizeMode(widthMode));
            SetHeightMode(ConvertFromStringToSizeMode(heightMode));
        }
        else
        {
            const SizeMode mode = ConvertFromStringToSizeMode(widthMode);
            SetWidthMode(mode);
            SetHeightMode(mode);
        }
    }

    float UIVisual::GetOriginX() const
    {
        return GetOrigin().X;
    }

    float UIVisual::GetOriginY() const
    {
        return GetOrigin().Y;
    }
    
    void UIVisual::SetOriginXY(float x, float y)
    {
        SetOrigin(Vector2(x, y));
    }

    const char* UIVisual::GetAnchorPointAsChars() const
    {
        return ConvertFromAnchorPointToString(GetAnchorPoint());
    }

    void UIVisual::SetAnchorPointByChars(const char* value)
    {
        SetAnchorPoint(ConvertFromStringToAnchorPoint(value));
    }

    const char* UIVisual::GetVisibilityAsChars() const
    {
        return ConvertFromVisibilityToString(GetVisibility());
    }

    void UIVisual::SetVisibilityByChars(const char* value)
    {
        SetVisibility(ConvertFromStringToVisibility(value));
    }
}