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

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool DynamicTexture2D::IsLocked() const
    {
        return false;
    }
}