namespace Bibim
{
    Vector3 UIWindow3D::GetLocalOffset() const
    {
        return localOffset;
    }

    Vector3 UIWindow3D::GetGlobalOffset() const
    {
        return globalOffset;
    }

    Vector2 UIWindow3D::GetRotationCenter() const
    {
        return rotationCenter;
    }

    Vector3 UIWindow3D::GetRotation() const
    {
        return rotation;
    }

    Vector2 UIWindow3D::GetScaleCenter() const
    {
        return scaleCenter;
    }

    Vector2 UIWindow3D::GetScale() const
    {
        return scale;
    }

    void UIWindow3D::SetScale(float value)
    {
        SetScale(Vector2(value, value));
    }
}