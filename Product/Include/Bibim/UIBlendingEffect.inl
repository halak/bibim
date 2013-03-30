namespace Bibim
{
    BlendMode UIBlendingEffect::GetMode() const
    {
        return mode;
    }

    void UIBlendingEffect::SetMode(BlendMode value)
    {
        mode = value;
    }
}