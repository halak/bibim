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

    void AxisAlignedBoxShape2D::SetMinXY(float x, float y)
    {
        SetMin(Vector2(x, y));
    }

    void AxisAlignedBoxShape2D::SetMaxXY(float x, float y)
    {
        SetMax(Vector2(x, y));
    }
}