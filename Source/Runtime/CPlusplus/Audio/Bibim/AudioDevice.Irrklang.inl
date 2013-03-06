namespace Bibim
{
    irrklang::ISoundEngine* AudioDevice::GetEngine() const
    {
        return engine;
    }

    float AudioDevice::GetDuration(const String& uri) const
    {
        return GetDurationByChars(uri.CStr());
    }
}