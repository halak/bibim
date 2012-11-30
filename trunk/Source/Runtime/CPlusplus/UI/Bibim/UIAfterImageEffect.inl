namespace Bibim
{
    int UIAfterImageEffect::GetSkippedFrames() const
    {
        return skippedFrames;
    }

    int UIAfterImageEffect::GetTotalFrames() const
    {
        return totalFrames;
    }

    bool UIAfterImageEffect::GetActive() const
    {
        return active;
    }

    void UIAfterImageEffect::SetActive(bool value)
    {
        active = value;
    }
}