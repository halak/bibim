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

    void BoxShape2D::SetOrientationXY(float x, float y)
    {
        SetOrientation(Vector2(x, y));
    }

    void BoxShape2D::SetExtensionXY(float x, float y)
    {
        SetExtension(Vector2(x, y));
    }
}