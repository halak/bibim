#pragma once
#ifndef __BIBIM_AUDIODEVICE_H__
#define __BIBIM_AUDIODEVICE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/String.h>
#   include <irrklang.h>

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

            private:
                irrklang::ISoundEngine* engine;
        };
    }

#   include <Bibim/AudioDevice.inl>

#endif