namespace Bibim
{
    UIAlignedFrame::Alignment UIAlignedFrame::GetAlign() const
    {
        return align;
    }
                
    Vector2 UIAlignedFrame::GetOffset() const
    {
        return offset;
    }

    float UIAlignedFrame::GetOffsetX() const
    {
        return offset.X;
    }

    float UIAlignedFrame::GetOffsetY() const
    {
        return offset.Y;
    }

    void UIAlignedFrame::SetOffsetX(float value)
    {
        SetOffset(Vector2(value, offset.Y));
    }

    void UIAlignedFrame::SetOffsetY(float value)
    {
        SetOffset(Vector2(offset.X, value));
    }

    Vector2 UIAlignedFrame::GetSize() const
    {
        return size;
    }
}