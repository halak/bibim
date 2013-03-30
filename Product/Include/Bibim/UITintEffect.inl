namespace Bibim
{
    Vector4 UITintEffect::GetValue() const
    {
        return value;
    }

    void UITintEffect::SetValue(Vector4 value)
    {
        this->value = value;
    }

    void UITintEffect::SetValueRGBA(float r, float g, float b, float a)
    {
        SetValue(Vector4(r, g, b, a));
    }
}