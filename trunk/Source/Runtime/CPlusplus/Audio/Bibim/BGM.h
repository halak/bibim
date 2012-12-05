#pragma once
#ifndef __BIBIM_BGM_H__
#define __BIBIM_BGM_H__

#   include <Bibim/FWD.h>
#   include <Bibim/TimelineGameModule.h>
#   include <Bibim/String.h>
#   include <irrklang.h>
#   include <vector>

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

                void Change(const String& name);

                inline AudioDevice* GetAudioDevice() const;
                void SetAudioDevice(AudioDevice* value);

                inline float GetVolume() const;
                void SetVolume(float value);

                inline bool GetMute() const;
                void SetMute(bool value);

                inline float GetCrossfadeTime() const;
                void SetCrossfadeTime(float value);

            private:
                void UpdateVolumes();
                void DropAliveBGM();
                void DropAllDeadBGMs();

                typedef std::pair<irrklang::ISound*, float> DeadBGM;

            private:
                AudioDevice* audioDevice;
                irrklang::ISound* aliveBGM;
                float aliveBGMVolume;
                String aliveBGMName;
                std::vector<DeadBGM> deadBGMs;
                float volume;
                float crossfadeTime;
                bool mute;
        };
    }

#   include <Bibim/BGM.inl>

#endif