namespace Bibim
{
    Vector2 SpatialObject2D::GetPosition() const
    {
        return position;
    }

    float SpatialObject2D::GetRotation() const
    {
        return rotation;
    }

    float SpatialObject2D::GetScale() const
    {
        return scale;
    }

    Vector2 SpatialObject2D::GetDirection() const
    {
        return direction;
    }

    void SpatialObject2D::SetPositionXY(float x, float y)
    {
        SetPosition(Vector2(x, y));
    }
}