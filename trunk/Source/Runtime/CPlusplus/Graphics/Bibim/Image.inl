namespace Bibim
{
    const URI& Image::GetTextureURI() const
    {
        return textureURI;
    }

    const Rect& Image::GetClippingRect() const
    {
        return clippingRect;
    }

    Texture2D* Image::GetRealTexture() const
    {
        return realTexture;
    }

    const Rect& Image::GetRealClippingRect() const
    {
        return realClippingRect;
    }

    const RectF& Image::GetNormalizedRealClippingRect() const
    {
        return normalizedRealClippingRect;
    }

    uint Image::GetRevision() const
    {
        return revision;
    }
}