namespace Bibim
{
    Vector2 SegmentShape2D::GetDirection() const
    {
        return direction;
    }

    float SegmentShape2D::GetFrontLength() const
    {
        return frontLength;
    }

    float SegmentShape2D::GetBackLength() const
    {
        return backLength;
    }

    float SegmentShape2D::GetLength() const
    {
        return GetFrontLength() + GetBackLength();
    }
}