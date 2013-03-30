namespace Bibim
{
    FontLibrary* Font::GetLibrary() const
    {
        return library;
    }

    void Font::SetShadowOffsetXY(float x, float y)
    {
        SetShadowOffset(Vector2(x, y));
    }

    Color Font::GetColor() const
    {
        return color;
    }

    void Font::SetColorRGB(byte r, byte g, byte b)
    {
        SetColor(Color(r, g, b));
    }

    Color Font::GetStrokeColor() const
    {
        return strokeColor;
    }

    void Font::SetStrokeColorRGB(byte r, byte g, byte b)
    {
        SetStrokeColor(Color(r, g, b));
    }

    Color Font::GetShadowColor() const
    {
        return shadowColor;
    }

    void Font::SetShadowColorRGB(byte r, byte g, byte b) 
    {
        SetShadowColor(Color(r, g, b));
    }

    float Font::GetSpacing() const
    {
        return spacing;
    }
}