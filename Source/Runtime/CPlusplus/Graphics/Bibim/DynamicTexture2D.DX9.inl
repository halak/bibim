namespace Bibim
{
    void* DynamicTexture2D::LockedInfo::GetBuffer()
    {
        return buffer;
    }

    int DynamicTexture2D::LockedInfo::GetPitch() const
    {
        return pitch;
    }

    Rect DynamicTexture2D::LockedInfo::GetRect() const
    {
        return rect;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool DynamicTexture2D::IsLocked() const
    {
        return isLocked;
    }
}