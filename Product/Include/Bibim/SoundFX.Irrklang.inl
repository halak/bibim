namespace Bibim
{
    void SoundFX::Pause()
    {
        SetInPauseAllSounds(true);
    }

    void SoundFX::Pause(int group)
    {
        SetInPauseAllSounds(group, true);
    }

    void SoundFX::Resume()
    {
        SetInPauseAllSounds(false);
    }

    void SoundFX::Resume(int group)
    {
        SetInPauseAllSounds(group, false);
    }

    AudioDevice* SoundFX::GetAudioDevice() const
    {
        return audioDevice;
    }

    float SoundFX::GetVolume() const
    {
        return volume;
    }

    bool SoundFX::GetMute() const
    {
        return mute;
    }
}