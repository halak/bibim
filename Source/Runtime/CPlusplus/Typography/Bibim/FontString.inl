namespace Bibim
{
    const String& FontString::GetText() const
    {
        return text;
    }

    Font* FontString::GetFont() const
    {
        return font;
    }

    Vector2 FontString::GetSize() const
    {
        return size;
    }

    const FontString::GlyphCollection& FontString::GetRegularGlyphs() const
    {
        return regularGlyphs;
    }

    const FontString::GlyphCollection& FontString::GetStrokedGlyphs() const
    {
        return strokedGlyphs;
    }

    const FontString::GlyphCollection& FontString::GetShadowGlyphs() const
    {
        return shadowGlyphs;
    }
}