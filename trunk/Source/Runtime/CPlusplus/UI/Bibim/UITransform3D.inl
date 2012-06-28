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

    void UITransform3D::SetLocalOffsetXYZ(float x, float y, float z)
    {
        SetLocalOffset(Vector3(x, y, z));
    }

    void UITransform3D::SetGlobalOffsetXYZ(float x, float y, float z)
    {
        SetGlobalOffset(Vector3(x, y, z));
    }

    void UITransform3D::SetRotationXYZ(float x, float y, float z)
    {
        SetRotation(Vector3(x, y, z));
    }

    void UITransform3D::SetRotationCenterXY(float x, float y)
    {
        SetRotationCenter(Vector2(x, y));
    }

    void UITransform3D::SetScaleXY(float x, float y)
    {
        SetScale(Vector2(x, y));
    }

    void UITransform3D::SetScaleCenterXY(float x, float y)
    {
        SetScaleCenter(Vector2(x, y));
    }
}