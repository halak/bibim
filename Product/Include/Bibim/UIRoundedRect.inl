namespace Bibim
{
    float UIRoundedRect::GetLeftTopRadius() const
    {
        return leftTop;
    }

    void UIRoundedRect::SetLeftTopRadius(float value)
    {
        leftTop = Math::Max(value, 0.0f);
    }

    float UIRoundedRect::GetRightTopRadius() const
    {
        return rightTop;
    }

    void UIRoundedRect::SetRightTopRadius(float value)
    {
        rightTop = Math::Max(value, 0.0f);
    }

    float UIRoundedRect::GetLeftBottomRadius() const
    {
        return leftBottom;
    }

    void UIRoundedRect::SetLeftBottomRadius(float value)
    {
        leftBottom = Math::Max(value, 0.0f);
    }

    float UIRoundedRect::GetRightBottomRadius() const
    {
        return rightBottom;
    }

    void UIRoundedRect::SetRightBottomRadius(float value)
    {
        rightBottom = Math::Max(value, 0.0f);
    }
    
    void UIRoundedRect::Setup(float leftTop, float rightTop, float leftBottom, float rightBottom)
    {
        SetLeftTopRadius(leftTop);
        SetRightTopRadius(rightTop);
        SetLeftBottomRadius(leftBottom);
        SetRightBottomRadius(rightBottom);
    }

    void UIRoundedRect::SetAllRadii(float value)
    {
        Setup(value, value, value, value);
    }

    void UIRoundedRect::SetLeftRadii(float value)
    {
        SetLeftTopRadius(value);
        SetLeftBottomRadius(value);
    }

    void UIRoundedRect::SetTopRadii(float value)
    {
        SetLeftTopRadius(value);
        SetRightTopRadius(value);
    }

    void UIRoundedRect::SetRightRadii(float value)
    {
        SetRightTopRadius(value);
        SetRightBottomRadius(value);
    }

    void UIRoundedRect::SetBottomRadii(float value)
    {
        SetLeftBottomRadius(value);
        SetRightBottomRadius(value);
    }
}