namespace Bibim
{
    Vector3 UITransform3D::GetLocalOffset() const
    {
        return localOffset;
    }

    Vector3 UITransform3D::GetGlobalOffset() const
    {
        return globalOffset;
    }

    Vector2 UITransform3D::GetRotationCenter() const
    {
        return rotationCenter;
    }

    Vector3 UITransform3D::GetRotation() const
    {
        return rotation;
    }

    Vector2 UITransform3D::GetScaleCenter() const
    {
        return scaleCenter;
    }

    Vector2 UITransform3D::GetScale() const
    {
        return scale;
    }

    void UITransform3D::SetScale(float value)
    {
        SetScale(Vector2(value, value));
    }
}