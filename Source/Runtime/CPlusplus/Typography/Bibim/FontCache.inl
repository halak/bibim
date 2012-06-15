namespace Bibim
{
    bool FontCacheParameters::operator != (const FontCacheParameters& right) const
    {
        return !operator == (right);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    FontLibrary* FontCache::GetLibrary() const
    {
        return library;
    }

    const FontCacheParameters& FontCache::GetParameters() const
    {
        return parameters;
    }

    float FontCache::GetAscender() const
    {
        return ascender;
    }

    float FontCache::GetDescender() const
    {
        return descender;
    }

    float FontCache::GetLineHeight() const
    {
        return lineHeight;
    }

    const GlyphTable* FontCache::GetRegularGlyphTable() const
    {
        return regularGlyphTable;
    }

    const GlyphTable* FontCache::GetStrokedGlyphTable() const
    {
        return strokedGlyphTable;
    }

    const GlyphTable* FontCache::GetGlowGlyphTable() const
    {
        return glowGlyphTable;
    }
}