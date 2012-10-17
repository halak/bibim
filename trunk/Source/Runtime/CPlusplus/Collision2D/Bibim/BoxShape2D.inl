namespace Bibim
{
    Vector2 BoxShape2D::GetOrientation() const
    {
        return orientation;
    }

    Vector2 BoxShape2D::GetExtension() const
    {
        return extension;
    }

    float BoxShape2D::GetOrientationX() const
    {
        return orientation.X;
    }

    float BoxShape2D::GetOrientationY() const
    {
        return orientation.Y;
    }

    void BoxShape2D::SetOrientationXY(float x, float y)
    {
        SetOrientation(Vector2(x, y));
    }

    float BoxShape2D::GetExtensionX() const
    {
        return extension.X;
    }

    float BoxShape2D::GetExtensionY() const
    {
        return extension.Y;
    }

    void BoxShape2D::SetExtensionXY(float x, float y)
    {
        SetExtension(Vector2(x, y));
    }
}