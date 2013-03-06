#include <Bibim/PCH.h>
#include <Bibim/AudioDevice.Android.h>
#include <Bibim/Assert.h>
#include <Bibim/MPQ.h>
#include <Bibim/MPQStream.h>

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