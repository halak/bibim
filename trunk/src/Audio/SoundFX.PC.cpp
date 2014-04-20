#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_PC))

#include <Bibim/SoundFX.PC.h>
#include <Bibim/Assert.h>
#include <Bibim/AudioDevice.PC.h>
#include <Bibim/AutoLocker.h>
#include <Bibim/Math.h>
#include <irrklang.h>
using namespace irrklang;

namespace Bibim
{
    class SoundFX::EventListener : public irrklang::ISoundStopEventReceiver
    {
        public:
            EventListener(SoundFX* sfx);

            virtual void OnSoundStopped(irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData);

        private:
            SoundFX* sfx;
    };

    SoundFX::SoundFX()
        : audioDevice(nullptr),
          volume(1.0f),
          mute(false)
    {
        eventListener = new EventListener(this);
    }

    SoundFX::SoundFX(AudioDevice* audioDevice)
        : audioDevice(audioDevice),
          volume(1.0f),
          mute(false)
    {
        eventListener = new EventListener(this);
    }

    SoundFX::~SoundFX()
    {
        DropAllSounds();
        delete eventListener;
    }

    void SoundFX::Update(float /*dt*/, int timestamp)
    {
        if (Seal(timestamp))
            return;

        StoppedSoundCollection temporaryStoppedSounds;
        {
            BBAutoLock(stoppedSoundsLock);
            temporaryStoppedSounds.swap(stoppedSounds);
        }

        for (StoppedSoundCollection::iterator it = temporaryStoppedSounds.begin(); it != temporaryStoppedSounds.end(); ++it)
            DropSound((*it).first, (*it).second);
    }

    void SoundFX::Play(const String& name, int group)
    {
        if (audioDevice == nullptr)
            return;

        SoundCollection* items = FindSounds(group);
        if (items == nullptr)
        {
            soundGroups.push_back(group);
            sounds.push_back(SoundCollection());
            items = &sounds.back();
        }

        if (ISoundEngine* engine = audioDevice->GetEngine())
        {
            if (ISound* sound = engine->play2D(name.CStr(), false, true))
            {
                if (mute)
                    sound->setVolume(0.0f);
                else
                    sound->setVolume(volume);
                sound->setSoundStopEventReceiver(eventListener, reinterpret_cast<void*>(group));
                sound->setIsPaused(false);
                items->push_back(sound);
            }
        }
    }

    void SoundFX::Stop()
    {
        soundGroups.clear();

        SoundDictionaryValues temporarySounds;
        temporarySounds.swap(sounds);

        for (SoundDictionaryValues::iterator itDict = temporarySounds.begin(); itDict != temporarySounds.end(); ++itDict)
        {
            SoundCollection& items = (*itDict);
            for (SoundCollection::iterator it = items.begin(); it != items.end(); ++it)
            {
                (*it)->setSoundStopEventReceiver(nullptr);
                (*it)->stop();
                (*it)->drop();
            }
        }
    }

    void SoundFX::Stop(int group)
    {
        if (SoundCollection* items = FindSounds(group))
        {
            SoundCollection temporaryItems;
            temporaryItems.swap(*items);

            for (SoundCollection::iterator it = temporaryItems.begin(); it != temporaryItems.end(); ++it)
            {
                (*it)->setSoundStopEventReceiver(nullptr);
                (*it)->stop();
                (*it)->drop();
            }
        }
    }

    void SoundFX::SetAudioDevice(AudioDevice* value)
    {
        if (audioDevice != value)
        {
            if (audioDevice)
                DropAllSounds();

            audioDevice = value;
        }
    }

    void SoundFX::SetVolume(float value)
    {
        value = Math::Clamp(value, 0.0f, 1.0f);

        if (volume != value)
        {
            volume = value;
            UpdateVolumes();
        }
    }

    void SoundFX::SetMute(bool value)
    {
        if (mute != value)
        {
            mute = value;
            UpdateVolumes();
        }
    }

    void SoundFX::UpdateVolumes()
    {
        if (mute)
        {
            for (SoundDictionaryValues::iterator itDict = sounds.begin(); itDict != sounds.end(); ++itDict)
            {
                SoundCollection& items = (*itDict);
                for (SoundCollection::iterator it = items.begin(); it != items.end(); ++it)
                    (*it)->setVolume(0.0f);
            }
        }
        else
        {
            for (SoundDictionaryValues::iterator itDict = sounds.begin(); itDict != sounds.end(); ++itDict)
            {
                SoundCollection& items = (*itDict);
                for (SoundCollection::iterator it = items.begin(); it != items.end(); ++it)
                    (*it)->setVolume(volume);
            }
        }
    }

    SoundFX::SoundCollection* SoundFX::FindSounds(int group)
    {
        for (SoundDictionaryKeys::iterator it = soundGroups.begin(); it != soundGroups.end(); ++it)
        {
            if ((*it) == group)
                return &sounds[it - soundGroups.begin()];
        }

        return nullptr;
    }

    const SoundFX::SoundCollection* SoundFX::FindSounds(int group) const
    {
        for (SoundDictionaryKeys::const_iterator it = soundGroups.begin(); it != soundGroups.end(); ++it)
        {
            if ((*it) == group)
                return &sounds[it - soundGroups.begin()];
        }

        return nullptr;
    }

    void SoundFX::SetInPauseAllSounds(bool value)
    {
        for (SoundDictionaryValues::iterator itDict = sounds.begin(); itDict != sounds.end(); ++itDict)
        {
            SoundCollection& items = (*itDict);
            for (SoundCollection::iterator it = items.begin(); it != items.end(); ++it)
                (*it)->setIsPaused(value);
        }
    }

    void SoundFX::SetInPauseAllSounds(int group, bool value)
    {
        if (SoundCollection* items = FindSounds(group))
        {
            for (SoundCollection::iterator it = items->begin(); it != items->end(); ++it)
                (*it)->setIsPaused(value);
        }
    }

    void SoundFX::DropSound(int group, irrklang::ISound* sound)
    {
        if (SoundCollection* items = FindSounds(group))
        {
            for (SoundCollection::iterator it = items->begin(); it != items->end(); ++it)
            {
                if ((*it) == sound)
                {
                    (*it)->setSoundStopEventReceiver(nullptr);
                    (*it)->drop();
                    items->erase(it);
                    break;
                }
            }
        }
    }

    void SoundFX::DropAllSounds()
    {
        soundGroups.clear();

        SoundDictionaryValues temporarySounds;
        temporarySounds.swap(sounds);

        for (SoundDictionaryValues::iterator itDict = temporarySounds.begin(); itDict != temporarySounds.end(); ++itDict)
        {
            SoundCollection& items = (*itDict);
            for (SoundCollection::iterator it = items.begin(); it != items.end(); ++it)
            {
                (*it)->setSoundStopEventReceiver(nullptr);
                (*it)->drop();
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    SoundFX::EventListener::EventListener(SoundFX* sfx)
        : sfx(sfx)
    {
    }

    void SoundFX::EventListener::OnSoundStopped(ISound* sound, E_STOP_EVENT_CAUSE reason, void* userData)
    {
        if (reason != irrklang::ESEC_SOUND_FINISHED_PLAYING)
            return;

        const int group = reinterpret_cast<int>(userData);
        AutoLocker locker(sfx->stoppedSoundsLock);
        sfx->stoppedSounds.push_back(std::pair<int, irrklang::ISound*>(group, sound));
    }
}

#endif