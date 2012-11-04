#include <Bibim/PCH.h>
#include <Bibim/AudioDevice.h>
#include <Bibim/Assert.h>
using namespace irrklang;

namespace Bibim
{
    AudioDevice::AudioDevice()
    {
        engine = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_PRINT_DEBUG_INFO_TO_DEBUGGER);
    }

    AudioDevice::~AudioDevice()
    {
        engine->drop();
        engine = nullptr;
    }
}