namespace Bibim
{
    FontLibrary* Font::GetLibrary() const
    {
        return library;
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

    Color Font::GetGlowColor() const
    {
        return glowColor;
    }

    void Font::SetGlowColorRGB(byte r, byte g, byte b) 
    {
        SetGlowColor(Color(r, g, b));
    }

    float Font::GetSpacing() const
    {
        return spacing;
    }
}