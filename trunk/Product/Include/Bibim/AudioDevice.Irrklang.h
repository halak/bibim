#pragma once
#ifndef __BIBIM_AUDIODEVICE_IRRKLANG_H__
#define __BIBIM_AUDIODEVICE_IRRKLANG_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/String.h>

    namespace irrklang { class ISoundEngine; }

    namespace Bibim
    {
        class AudioDevice : public GameModule
        {
            BBModuleClass(AudioDevice, GameModule, 'A', 'U', 'D', 'D');
            public:
                AudioDevice();
                virtual ~AudioDevice();

                void AddArchive(MPQ* mpq);

                inline irrklang::ISoundEngine* GetEngine() const;

                inline float GetDuration(const String& uri) const;
                float GetDurationByChars(const char* uri) const;

            private:
                irrklang::ISoundEngine* engine;
        };
    }

#   include <Bibim/AudioDevice.Irrklang.inl>

#endif