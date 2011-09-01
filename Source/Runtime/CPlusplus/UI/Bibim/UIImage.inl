namespace Bibim
{
    const URI& UIImage::GetTextureURI() const
    {
        return textureURI;
    }

    const Rectangle& UIImage::GetClippingRectangle() const
    {
        return clippingRectangle;
    }

    Texture2D* UIImage::GetRealTexture() const
    {
        return realTexture;
    }

    const Rectangle& UIImage::GetRealClippingRectangle() const
    {
        return realClippingRectangle;
    }

    const RectangleF& UIImage::GetNormalizedRealClippingRectangle() const
    {
        return normalizedRealClippingRectangle;
    }

    uint UIImage::GetRevision() const
    {
        return revision;
    }
}