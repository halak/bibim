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

    void UIColorMatrixEffect::Tint(Vector3 value)
    {
        red = Vector4(value.X, 0.0f, 0.0f, 0.0f);
        green = Vector4(0.0f, value.Y, 0.0f, 0.0f);
        blue = Vector4(0.0f, 0.0f, value.Z, 0.0f);
    }
    
    void UIColorMatrixEffect::TintRGB(float r, float g, float b)
    {
        Tint(Vector3(r, g, b));
    }

    void UIColorMatrixEffect::Fill(Vector3 value)
    {
        red = Vector4(0.0f, 0.0f, 0.0f, value.X);
        green = Vector4(0.0f, 0.0f, 0.0f, value.Y);
        blue = Vector4(0.0f, 0.0f, 0.0f, value.Z);
    }

    void UIColorMatrixEffect::FillRGB(float r, float g, float b)
    {
        Fill(Vector3(r, g, b));
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