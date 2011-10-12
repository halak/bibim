namespace Bibim
{
    const RectF& UIFixedFrame::GetRect() const
    {
        return rect;
    }

    void UIFixedFrame::SetRect(const RectF& value)
    {
        rect = value;
    }
}