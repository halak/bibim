namespace Bibim
{
    GraphicsDevice* FontLibrary::GetGraphicsDevice() const
    {
        return graphicsDevice;
    }

    const String& FontLibrary::GetOSFontDirectory() const
    {
        return osFontDirectory;
    }

    const String& FontLibrary::GetAlternativeFace() const
    {
        return alternativeFace;
    }

    void* FontLibrary::GetFTLibrary() const
    {
        return ftLibrary;
    }
}