#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_ANDROID))

#include <Bibim/AudioDevice.Android.h>
#include <Bibim/Assert.h>
#include <Bibim/Log.h>

namespace Bibim
{
    AudioDevice::AudioDevice()
    {
    }

    AudioDevice::~AudioDevice()
    {
    }

    float AudioDevice::GetDurationByChars(const char* /*uri*/) const
    {
        return 0.0f;
    }
}

#endif