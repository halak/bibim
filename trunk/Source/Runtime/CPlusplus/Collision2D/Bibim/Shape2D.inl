namespace Bibim
{
    Shape2D::Type Shape2D::GetType() const
    {
        return type;
    }

    Vector2 Shape2D::GetPosition() const
    {
        return position;
    }

    float Shape2D::GetRotation() const
    {
        return rotation;
    }

    float Shape2D::GetScale() const
    {
        return scale;
    }

    int Shape2D::GetSpatialRevision() const
    {
        return revision;
    }

    float Shape2D::GetPositionX() const
    {
        return position.X;
    }

    float Shape2D::GetPositionY() const
    {
        return position.Y;
    }

    void Shape2D::SetPositionXY(float x, float y)
    {
        SetPosition(Vector2(x, y));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::list<Vector2>& Shape2D::SimpleVertices::GetData() const
    {
        return v;
    }
}