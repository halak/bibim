namespace Bibim
{
    GraphicsDevice* Texture2D::GetGraphicsDevice() const
    {
        return graphicsDevice;
    }
    
    int Texture2D::GetWidth() const
    {
        return width;
    }

    int Texture2D::GetHeight() const
    {
        return height;
    }

    int Texture2D::GetSurfaceWidth() const
    {
        return surfaceWidth;
    }

    int Texture2D::GetSurfaceHeight() const
    {
        return surfaceHeight;
    }

    Texture2D::PixelFormat Texture2D::GetPixelFormat() const
    {
        return pixelFormat;
    }
}