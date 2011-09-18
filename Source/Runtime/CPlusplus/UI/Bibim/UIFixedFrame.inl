namespace Bibim
{
    const RectF& UIFixedFrame::GetRect() const
    {
        return Rect;
    }

    void UIFixedFrame::SetRect(const RectF& value)
    {
        Rect = value;
    }
}