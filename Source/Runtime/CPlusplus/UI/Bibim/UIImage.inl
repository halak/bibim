namespace Bibim
{
    Image* UIImage::GetSource() const
    {
        return source;
    }

    bool UIImage::GetAutoResize() const
    {
        return autoResize;
    }

    void UIImage::SetAutoResize(bool value)
    {
        autoResize = value;
    }

    bool UIImage::GetHorizontalFlip() const
    {
        return horizontalFlip;
    }

    void UIImage::SetHorizontalFlip(bool value)
    {
        horizontalFlip = value;
    }

    bool UIImage::GetVerticalFlip() const
    {
        return verticalFlip;
    }

    void UIImage::SetVerticalFlip(bool value)
    {
        verticalFlip = value;
    }

    BitMask* UIImage::GetMask() const
    {
        return mask;
    }

    void UIImage::SetMask(BitMask* value)
    {
        mask = value;
    }
}