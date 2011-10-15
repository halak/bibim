namespace Bibim
{
    const String& Image::GetTextureURI() const
    {
        return textureURI;
    }

    const Rect& Image::GetClippingRect() const
    {
        return clippingRect;
    }
    
    const RectF& Image::GetNormalizedClippingRect() const
    {
        return normalizedClippingRect;
    }

    Texture2D* Image::GetTexture() const
    {
        return texture;
    }
}