namespace Bibim
{
    void UIColorMatrixEffect::Reset()
    {
        red = DefaultRed;
        green = DefaultGreen;
        blue = DefaultBlue;
    }

    void UIColorMatrixEffect::Grayscale(Vector4 value)
    {
        red = value;
        green = value;
        blue = value;
    }

    void UIColorMatrixEffect::GrayscaleRGBA(float r, float g, float b, float a)
    {
        red = Vector4(r, g, b, a);
        green = Vector4(r, g, b, a);
        blue = Vector4(r, g, b, a);
    }

    Vector4 UIColorMatrixEffect::GetRed() const
    {
        return red;
    }

    void UIColorMatrixEffect::SetRed(Vector4 value)
    {
        red = value;
    }

    void UIColorMatrixEffect::SetRedRGBA(float r, float g, float b, float a)
    {
        red = Vector4(r, g, b, a);
    }

    Vector4 UIColorMatrixEffect::GetGreen() const
    {
        return green;
    }

    void UIColorMatrixEffect::SetGreen(Vector4 value)
    {
        green = value;
    }

    void UIColorMatrixEffect::SetGreenRGBA(float r, float g, float b, float a)
    {
        green = Vector4(r, g, b, a);
    }

    Vector4 UIColorMatrixEffect::GetBlue() const
    {
        return blue;
    }

    void UIColorMatrixEffect::SetBlue(Vector4 value)
    {
        blue = value;
    }

    void UIColorMatrixEffect::SetBlueRGBA(float r, float g, float b, float a)
    {
        blue = Vector4(r, g, b, a);
    }
}