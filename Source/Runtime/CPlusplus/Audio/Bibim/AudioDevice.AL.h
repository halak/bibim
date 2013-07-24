#pragma once
#ifndef __BIBIM_AUDIODEVICE_ANDROID_H__
#define __BIBIM_AUDIODEVICE_ANDROID_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        class AudioDevice : public GameModule
        {
            BBModuleClass(AudioDevice, GameModule, 'A', 'U', 'D', 'D');
            public:
                AudioDevice();
                virtual ~AudioDevice();

                inline float GetDuration(const String& uri) const;
                float GetDurationByChars(const char* uri) const;
        };
    }

#endif