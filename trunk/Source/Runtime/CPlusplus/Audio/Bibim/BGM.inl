namespace Bibim
{
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