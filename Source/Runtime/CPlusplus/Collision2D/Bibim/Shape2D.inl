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
}