namespace Bibim
{
    Vector2 AxisAlignedBoxShape2D::GetMin() const
    {
        return min;
    }

    Vector2 AxisAlignedBoxShape2D::GetMax() const
    {
        return max;
    }

    float AxisAlignedBoxShape2D::GetMinX() const
    {
        return min.X;
    }

    float AxisAlignedBoxShape2D::GetMinY() const
    {
        return min.Y;
    }

    void AxisAlignedBoxShape2D::SetMinXY(float x, float y)
    {
        SetMin(Vector2(x, y));
    }

    float AxisAlignedBoxShape2D::GetMaxX() const
    {
        return max.X;
    }

    float AxisAlignedBoxShape2D::GetMaxY() const
    {
        return max.Y;
    }

    void AxisAlignedBoxShape2D::SetMaxXY(float x, float y)
    {
        SetMax(Vector2(x, y));
    }
}