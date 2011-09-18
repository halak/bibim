namespace Bibim
{
    const URI& UIImage::GetTextureURI() const
    {
        return textureURI;
    }

    const Rect& UIImage::GetClippingRect() const
    {
        return clippingRect;
    }

    Texture2D* UIImage::GetRealTexture() const
    {
        return realTexture;
    }

    const Rect& UIImage::GetRealClippingRect() const
    {
        return realClippingRect;
    }

    const RectF& UIImage::GetNormalizedRealClippingRect() const
    {
        return normalizedRealClippingRect;
    }

    uint UIImage::GetRevision() const
    {
        return revision;
    }
}