namespace Bibim
{
    const RectangleStorage& GlyphSurface::GetStorage() const
    {
        return *storage;
    }

    Texture2D* GlyphSurface::GetTexture() const
    {
        return StaticCast<Texture2D>(texture);
    }
}