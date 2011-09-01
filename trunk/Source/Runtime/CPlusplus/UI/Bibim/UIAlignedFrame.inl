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

    Vector2 UIAlignedFrame::GetSize() const
    {
        return size;
    }
}