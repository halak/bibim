#include <Bibim/Config.h>
#include <Bibim/AudioDevice.AL.h>
#include <Bibim/Assert.h>

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