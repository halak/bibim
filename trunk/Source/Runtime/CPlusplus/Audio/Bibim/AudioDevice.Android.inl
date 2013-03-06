namespace Bibim
{
    float AudioDevice::GetDuration(const String& uri) const
    {
        return GetDurationByChars(uri.CStr());
    }
}