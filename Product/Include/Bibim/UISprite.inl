namespace Bibim
{
    Sprite* UISprite::GetSource() const
    {
        return source;
    }

    float UISprite::GetSpeed() const
    {
        return speed;
    }

    float UISprite::GetTime() const
    {
        return time;
    }

    int UISprite::GetFrameIndex() const
    {
        return frameIndex;
    }

    bool UISprite::GetHorizontalFlip() const
    {
        return horizontalFlip;
    }

    void UISprite::SetHorizontalFlip(bool value)
    {
        horizontalFlip = value;
    }

    bool UISprite::GetVerticalFlip() const
    {
        return verticalFlip;
    }

    void UISprite::SetVerticalFlip(bool value)
    {
        verticalFlip = value;
    }

    Timeline* UISprite::GetTimeline() const
    {
        return timeline;
    }
}