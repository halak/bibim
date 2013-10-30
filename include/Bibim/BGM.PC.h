#pragma once
#ifndef __BIBIM_BGM_PC_H__
#define __BIBIM_BGM_PC_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_PLATFORM_PC))

#include <Bibim/TimelineGameModule.h>
#include <Bibim/Lock.h>
#include <Bibim/String.h>
#include <vector>

namespace irrklang { class ISound; };

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
            inline void Change(const String& name, float rewindTime);

            inline AudioDevice* GetAudioDevice() const;
            void SetAudioDevice(AudioDevice* value);

            inline float GetVolume() const;
            void SetVolume(float value);

            inline bool GetMute() const;
            void SetMute(bool value);

            inline float GetCrossfadeTime() const;
            void SetCrossfadeTime(float value);

        protected:
            inline void Rewind();
            void Rewind(float time);
            float GetPlayTime() const;

        private:
            void Change(const String& name, float rewindTime, float startTime);

            void UpdateVolumes();
            void DropAliveBGM();
            void DropAllDeadBGMs();

            typedef std::pair<irrklang::ISound*, float> DeadBGM;

        private:
            class EventListener;

        private:
            AudioDevice* audioDevice;
            irrklang::ISound* aliveBGM;
            float aliveBGMVolume;
            String aliveBGMName;
            std::vector<DeadBGM> deadBGMs;
            float volume;
            float crossfadeTime;
            EventListener* eventListener;
            Lock bgmRewindLock;
            float bgmRewindTime;
            bool mute;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

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

    void BGM::Rewind()
    {
        Rewind(0.0f);
    }
}

#endif
#endif