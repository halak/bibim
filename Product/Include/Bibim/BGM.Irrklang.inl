namespace Bibim
{
    void BGM::Change(const String& name)
    {
        Change(name, 0.0f, 0.0f);
    }

    void BGM::Change(const String& name, float rewindTime)
    {
        Change(name, rewindTime, 0.0f);
    }

    AudioDevice* BGM::GetAudioDevice() const
    {
        return audioDevice;
    }

    float BGM::GetVolume() const
    {
        return volume;
    }

    bool BGM::GetMute() const
    {
        return mute;
    }

    float BGM::GetCrossfadeTime() const
    {
        return crossfadeTime;
    }
}