#pragma once
#ifndef __BIBIM_BGM_ANDROID_H__
#define __BIBIM_BGM_ANDROID_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_PLATFORM_ANDROID))

#include <Bibim/TimelineGameModule.h>
#include <Bibim/String.h>
#include <vector>

namespace Bibim
{
    class BGM : public TimelineGameModule
    {
        BBModuleClass(BGM, TimelineGameModule, 'B', 'G', 'M', 'M');
        public:
            BGM();
            BGM(AudioDevice* audioDevice);
            virtual ~BGM();

            virtual void Update(float dt, int timestamp);

            inline void Change(const String& name);
            void Change(const String& name, float rewindTime);

            inline AudioDevice* GetAudioDevice() const;
            void SetAudioDevice(AudioDevice* value);

            inline float GetVolume() const;
            void SetVolume(float value);

            inline bool GetMute() const;
            void SetMute(bool value);

            inline float GetCrossfadeTime() const;
            void SetCrossfadeTime(float value);

        protected:
            void Rewind() { }
            void Rewind(float /*time*/) { }
            float GetPlayTime() const { return 0.0f; }

        private:
            void UpdateVolumes();
            void DropAliveBGM();
            void DropAllDeadBGMs();

            typedef std::pair<void*, float> DeadBGM;

        private:
            AudioDevice* audioDevice;
            void* aliveBGM;
            float aliveBGMVolume;
            String aliveBGMName;
            std::vector<DeadBGM> deadBGMs;
            float volume;
            float crossfadeTime;
            bool mute;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void BGM::Change(const String& name)
    {
        Change(name, 0.0f);
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

#endif
#endif