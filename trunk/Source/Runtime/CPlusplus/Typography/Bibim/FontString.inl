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

    const FontString::GlyphCollection& FontString::GetRegularGlyphs() const
    {
        return regularGlyphs;
    }

    const FontString::GlyphCollection& FontString::GetStrokedGlyphs() const
    {
        return strokedGlyphs;
    }

    const FontString::GlyphCollection& FontString::GetGlowGlyphs() const
    {
        return glowGlyphs;
    }
}