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

    float SpatialObject2D::GetPositionX() const
    {
        return position.X;
    }

    float SpatialObject2D::GetPositionY() const
    {
        return position.Y;
    }

    void SpatialObject2D::SetPositionXY(float x, float y)
    {
        SetPosition(Vector2(x, y));
    }
}