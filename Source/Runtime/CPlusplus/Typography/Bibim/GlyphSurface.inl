namespace Bibim
{
    const RectStorage& GlyphSurface::GetStorage() const
    {
        return *storage;
    }

    Texture2D* GlyphSurface::GetTexture() const
    {
        return StaticCast<Texture2D>(texture);
    }
}