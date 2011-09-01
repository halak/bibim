namespace Bibim
{
    const GlyphTable::GlyphDictionary& GlyphTable::GetGlyphs() const
    {
        return glyphs;
    }

    const GlyphTable::SurfaceCollection& GlyphTable::GetSurfaces() const
    {
        return surfaces;
    }
}