#pragma once
#ifndef __BIBIM_SOUNDFX_ANDROID_H__
#define __BIBIM_SOUNDFX_ANDROID_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_PLATFORM_ANDROID))

#include <Bibim/TimelineGameModule.h>
#include <Bibim/Lock.h>
#include <Bibim/String.h>
#include <vector>

namespace Bibim
{
    class SoundFX : public TimelineGameModule
    {
        BBModuleClass(SoundFX, TimelineGameModule, 'S', 'D', 'F', 'X');
        public:
            SoundFX();
            SoundFX(AudioDevice* audioDevice);
            virtual ~SoundFX();

            virtual void Update(float dt, int timestamp);

            void Play(const String& name, int group);
            void Stop();
            void Stop(int group);
            inline void Pause();
            inline void Pause(int group);
            inline void Resume();
            inline void Resume(int group);

            inline bool IsPlaying() const { return false; }  // NOT IMPLEMENTED
            inline bool IsPlaying(int group) const { return false; }  // NOT IMPLEMENTED

            inline AudioDevice* GetAudioDevice() const;
            void SetAudioDevice(AudioDevice* value);

            inline float GetVolume() const;
            void SetVolume(float value);

            inline bool GetMute() const;
            void SetMute(bool value);

        private:
            typedef std::vector<uint>            SoundCollection;
            typedef std::vector<int>             SoundDictionaryKeys;
            typedef std::vector<SoundCollection> SoundDictionaryValues;
            typedef std::vector<std::pair<int, uint> > StoppedSoundCollection;

            void UpdateVolumes();
            SoundCollection* FindSounds(int group);
            const SoundCollection* FindSounds(int group) const;
            void SetInPauseAllSounds(bool value);
            void SetInPauseAllSounds(int group, bool value);
            void DropSound(int group, uint sound);
            void DropAllSounds();

        private:
            AudioDevice* audioDevice;
            SoundDictionaryKeys   soundGroups;
            SoundDictionaryValues sounds;
            float volume;
            bool mute;
            Lock stoppedSoundsLock;
            StoppedSoundCollection stoppedSounds;
            //EventListener* eventListener;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

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

#endif
#endif