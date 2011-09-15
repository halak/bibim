namespace Bibim
{
    GraphicsDevice* Texture2D::GetGraphicsDevice()
    {
        return graphicsDevice;
    }

    bool Texture2D::GetTextureChanged() const
    {
        return textureChanged;
    }

    void Texture2D::SetTextureChanged(bool value)
    {
        textureChanged = value;
    }
}