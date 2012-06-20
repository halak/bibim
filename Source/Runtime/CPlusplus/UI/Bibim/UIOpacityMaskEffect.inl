namespace Bibim
{
    float UIOpacityMaskEffect::GetStartPoint() const
    {
        return startPoint;
    }

    float UIOpacityMaskEffect::GetLength() const
    {
        return length;
    }

    UIOpacityMaskEffect::FillStyle UIOpacityMaskEffect::GetFill() const
    {
        return fill;
    }

    const char* UIOpacityMaskEffect::GetFillAsChars() const
    {
        return ConvertFromFillStyleToString(GetFill());
    }

    void UIOpacityMaskEffect::SetFillByChars(const char* value)
    {
        if (value)
            SetFill(ConvertFromStringToFillStyle(value));
    }
}