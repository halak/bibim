#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_PC))

#include <Bibim/BGM.PC.h>
#include <Bibim/Assert.h>
#include <Bibim/AutoLocker.h>
#include <Bibim/AudioDevice.PC.h>
#include <Bibim/Math.h>
#include <irrklang.h>
using namespace irrklang;

namespace Bibim
{
    union FloatOrPointer
    {
        float asFloat;
        void* asPointer;
    };

    class BGM::EventListener : public irrklang::ISoundStopEventReceiver
    {
        public:
            EventListener(BGM* bgm);

            virtual void OnSoundStopped(irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData);

        private:
            BGM* bgm;
    };

    BGM::BGM()
        : audioDevice(nullptr),
          aliveBGM(nullptr),
          aliveBGMVolume(0.0f),
          volume(1.0f),
          crossfadeTime(1.0f),
          bgmRewindTime(0.0f),
          mute(false)
    {
        eventListener = new EventListener(this);
    }

    BGM::BGM(AudioDevice* audioDevice)
        : audioDevice(audioDevice),
          aliveBGM(nullptr),
          aliveBGMVolume(0.0f),
          volume(1.0f),
          crossfadeTime(1.0f),
          bgmRewindTime(0.0f),
          mute(false)
    {
        eventListener = new EventListener(this);
    }

    BGM::~BGM()
    {
        DropAliveBGM();
        DropAllDeadBGMs();
        delete eventListener;
    }

    void BGM::Update(float dt, int timestamp)
    {
        if (Seal(timestamp))
            return;

        if (bgmRewindTime > 0.0f)
        {
            float rewindTime = 0.0f;
            {
                BBAutoLock(bgmRewindLock);
                rewindTime = bgmRewindTime;
                bgmRewindTime = 0.0f;
            }

            const String name = aliveBGMName;
            DropAliveBGM();
            Change(name, rewindTime, rewindTime);
        }

        if (crossfadeTime > 0.0f)
        {
            const float vd = (1.0f / crossfadeTime) * dt;

            aliveBGMVolume = Math::Min(aliveBGMVolume + vd, 1.0f);

            for (std::vector<DeadBGM>::iterator it = deadBGMs.begin(); it != deadBGMs.end();)
            {
                ISound* sound  = (*it).first;
                float&  volume = (*it).second;

                volume -= vd;
                if (volume <= 0.0f)
                {
                    sound->setSoundStopEventReceiver(nullptr);
                    sound->setVolume(0.0f);
                    sound->drop();
                    it = deadBGMs.erase(it);
                }
                else
                    it++;
            }

            UpdateVolumes();
        }
    }

    void BGM::Change(const String& name, float rewindTime, float startTime)
    {
        if (name == aliveBGMName)
            return;

        if (crossfadeTime > 0.0f)
        {
            if (aliveBGM)
            {
                deadBGMs.push_back(DeadBGM(aliveBGM, aliveBGMVolume));
                aliveBGM = nullptr;
            }
        }
        else
            DropAliveBGM();

        if (name.IsEmpty() == false)
        {
            if (crossfadeTime > 0.0f)
                aliveBGMVolume = 0.0f;
            else
                aliveBGMVolume = 1.0f;

            irrklang::ISoundEngine* engine = audioDevice->GetEngine();

            const bool track = startTime > 0.0f;
            if (rewindTime > 0.0f)
            {
                aliveBGM = engine->play2D(name.CStr(), false, true, track, ESM_AUTO_DETECT, false);
                if (aliveBGM)
                {
                    FloatOrPointer u;
                    u.asFloat = rewindTime;
                    aliveBGM->setSoundStopEventReceiver(eventListener, u.asPointer);
                }
            }
            else
                aliveBGM = engine->play2D(name.CStr(), true, true, track, ESM_AUTO_DETECT, false);

            if (track)
            {
                const int positionInMS = static_cast<int>(startTime * 1000.0f);
                aliveBGM->setPlayPosition(positionInMS);
            }

            UpdateVolumes();

            if (aliveBGM)
                aliveBGM->setIsPaused(false);
        }

        aliveBGMName = name;
    }

    void BGM::SetAudioDevice(AudioDevice* value)
    {
        if (audioDevice != value)
        {
            const String name = aliveBGMName;

            if (audioDevice)
            {
                DropAliveBGM();
                DropAllDeadBGMs();
            }

            audioDevice = value;

            Change(name);
        }
    }

    void BGM::SetVolume(float value)
    {
        value = Math::Clamp(value, 0.0f, 1.0f);

        if (volume != value)
        {
            volume = value;
            UpdateVolumes();
        }
    }

    void BGM::SetMute(bool value)
    {
        if (mute != value)
        {
            mute = value;
            UpdateVolumes();
        }
    }

    void BGM::SetCrossfadeTime(float value)
    {
        value = Math::Clamp(value, 0.0f, 10.0f);

        if (crossfadeTime != value)
        {
            crossfadeTime = value;

            if (crossfadeTime == 0.0f)
            {
                aliveBGMVolume = 1.0f;
                DropAllDeadBGMs();
                UpdateVolumes();
            }
        }
    }

    void BGM::Rewind(float time)
    {
        if (aliveBGM)
            aliveBGM->setPlayPosition(static_cast<irrklang::ik_u32>(time * 1000.0f));
    }

    float BGM::GetPlayTime() const
    {
        if (aliveBGM)
            return static_cast<float>(aliveBGM->getPlayPosition()) * 0.001f;
        else
            return 0.0f;
    }

    void BGM::UpdateVolumes()
    {
        if (mute)
        {
            if (aliveBGM)
                aliveBGM->setVolume(0.0f);

            for (std::vector<DeadBGM>::iterator it = deadBGMs.begin(); it != deadBGMs.end(); it++)
                (*it).first->setVolume(0.0f);
        }
        else
        {
            if (aliveBGM)
                aliveBGM->setVolume(volume * aliveBGMVolume);

            for (std::vector<DeadBGM>::iterator it = deadBGMs.begin(); it != deadBGMs.end(); it++)
                (*it).first->setVolume(volume * (*it).second);
        }
    }

    void BGM::DropAliveBGM()
    {
        if (aliveBGM)
        {
            aliveBGM->setSoundStopEventReceiver(nullptr);
            aliveBGM->setVolume(0.0f);
            aliveBGM->drop();
            aliveBGM = nullptr;
        }

        aliveBGMName = String::Empty;
    }

    void BGM::DropAllDeadBGMs()
    {
        std::vector<DeadBGM> temporaryDeadBGMs;
        temporaryDeadBGMs.swap(deadBGMs);
        for (std::vector<DeadBGM>::iterator it = temporaryDeadBGMs.begin(); it != temporaryDeadBGMs.end(); it++)
        {
            ISound* sound = (*it).first;
            sound->setSoundStopEventReceiver(nullptr);
            sound->setVolume(0.0f);
            sound->drop();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    BGM::EventListener::EventListener(BGM* bgm)
        : bgm(bgm)
    {
    }

    void BGM::EventListener::OnSoundStopped(ISound* sound, E_STOP_EVENT_CAUSE reason, void* userData)
    {
        if (reason != irrklang::ESEC_SOUND_FINISHED_PLAYING)
            return;

        FloatOrPointer u;
        u.asPointer = userData;

        AutoLocker lock(bgm->bgmRewindLock);
        bgm->bgmRewindTime = u.asFloat;
    }
}

#endif