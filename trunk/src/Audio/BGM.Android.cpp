#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_ANDROID))

#include <Bibim/BGM.Android.h>
#include <Bibim/Assert.h>
#include <Bibim/AudioDevice.Android.h>
#include <Bibim/Math.h>
#include <Bibim/GameFramework.h>

namespace Bibim
{
    BGM::BGM()
        : audioDevice(nullptr),
          aliveBGM(nullptr),
          aliveBGMVolume(0.0f),
          volume(1.0f),
          crossfadeTime(1.0f),
          mute(false)
    {
    }

    BGM::BGM(AudioDevice* audioDevice)
        : audioDevice(audioDevice),
          aliveBGM(nullptr),
          aliveBGMVolume(0.0f),
          volume(1.0f),
          crossfadeTime(1.0f),
          mute(false)
    {
    }

    BGM::~BGM()
    {
        DropAliveBGM();
        DropAllDeadBGMs();
    }

    void BGM::Update(float dt, int timestamp)
    {
        if (Seal(timestamp))
            return;

        if (crossfadeTime > 0.0f)
        {
            const float vd = (1.0f / crossfadeTime) * dt;

            aliveBGMVolume = Math::Min(aliveBGMVolume + vd, 1.0f);

            for (std::vector<DeadBGM>::iterator it = deadBGMs.begin(); it != deadBGMs.end();)
            {
                void* sound  = (*it).first;
                float&  volume = (*it).second;

                volume -= vd;
                if (volume <= 0.0f)
                {
                    // sound->setVolume(0.0f);
                    // sound->drop();
                    it = deadBGMs.erase(it);
                }
                else
                    ++it;
            }

            UpdateVolumes();
        }
    }

    void BGM::Change(const String& name, float rewindTime)
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

            GameFramework::PlayBGM(name);
            //irrklang::ISoundEngine* engine = audioDevice->GetEngine();
            //aliveBGM = engine->play2D(name.CStr(), true, true, false, ESM_AUTO_DETECT, false);

            UpdateVolumes();

            //if (aliveBGM)
            //    aliveBGM->setIsPaused(false);
        }

        aliveBGMName = name;
    }

    void BGM::SetAudioDevice(AudioDevice* value)
    {
        if (audioDevice != value)
        {
            if (audioDevice)
            {
                DropAliveBGM();
                DropAllDeadBGMs();
            }

            audioDevice = value;

            Change(aliveBGMName);
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

    void BGM::UpdateVolumes()
    {
        if (mute)
        {
            GameFramework::SetBGMVolume(0.0f);
            //if (aliveBGM)
            //    aliveBGM->setVolume(0.0f);

            //for (std::vector<DeadBGM>::iterator it = deadBGMs.begin(); it != deadBGMs.end(); ++it)
            //    (*it).first->setVolume(0.0f);
        }
        else
        {
            GameFramework::SetBGMVolume(volume * aliveBGMVolume);
            //if (aliveBGM)
            //    aliveBGM->setVolume(volume * aliveBGMVolume);

            //for (std::vector<DeadBGM>::iterator it = deadBGMs.begin(); it != deadBGMs.end(); ++it)
            //    (*it).first->setVolume(volume * (*it).second);
        }
    }

    void BGM::DropAliveBGM()
    {
        GameFramework::SetBGMVolume(0.0f);
        /*
        if (aliveBGM)
        {
            aliveBGM->setVolume(0.0f);
            aliveBGM->drop();
            aliveBGM = nullptr;
        }
        */
    }

    void BGM::DropAllDeadBGMs()
    {
        std::vector<DeadBGM> temporaryDeadBGMs;
        temporaryDeadBGMs.swap(deadBGMs);
        for (std::vector<DeadBGM>::iterator it = temporaryDeadBGMs.begin(); it != temporaryDeadBGMs.end(); ++it)
        {
            /*
            (*it).first->setVolume(0.0f);
            (*it).first->drop();
            */
        }
    }
}

#endif