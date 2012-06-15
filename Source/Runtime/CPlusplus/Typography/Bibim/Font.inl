namespace Bibim
{
    FontLibrary* Font::GetLibrary() const
    {
        return library;
    }

    void Font::SetFaceURIByChars(const char* value)
    {
        if (value)
            SetFaceURI(value);
    }

    Color Font::GetColor() const
    {
        return color;
    }

    Color Font::GetStrokeColor() const
    {
        return strokeColor;
    }

    Color Font::GetGlowColor() const
    {
        return glowColor;
    }

    float Font::GetSpacing() const
    {
        return spacing;
    }
}