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

    Image::Transform Image::GetAppliedTransform() const
    {
        return appliedTransform;
    }

    int Image::GetWidth() const
    {
        return width;
    }

    int Image::GetHeight() const
    {
        return height;
    }

    Texture2D* Image::GetTexture() const
    {
        return texture;
    }
}