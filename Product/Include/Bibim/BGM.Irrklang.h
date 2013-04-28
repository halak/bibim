#pragma once
#ifndef __BIBIM_BGM_IRRKLANG_H__
#define __BIBIM_BGM_IRRKLANG_H__

#   include <Bibim/FWD.h>
#   include <Bibim/TimelineGameModule.h>
#   include <Bibim/Lock.h>
#   include <Bibim/String.h>
#   include <vector>

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
                void Rewind();
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
    }

#   include <Bibim/BGM.Irrklang.inl>

#endif