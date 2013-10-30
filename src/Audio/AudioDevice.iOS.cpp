#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_IOS))

#include <Bibim/AudioDevice.iOS.h>
#include <Bibim/Assert.h>
#include <Bibim/Log.h>

namespace Bibim
{
    AudioDevice::AudioDevice()
    {
        /*
        const ALCchar* defaultDeviceName = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
        Log::Information(String::CFormat("%s", defaultDeviceName));
        
        ALCdevice* device = alcOpenDevice(defaultDeviceName);
        ALCcontext* context = alcCreateContext(device, nullptr);

        Log::Information(String::CFormat("%s", alcGetString(device, ALC_DEVICE_SPECIFIER)));

        bool b = alcMakeContextCurrent(context);
        b = b;
        */

        /*
    ALDeviceList *pDeviceList = NULL;
    ALCcontext *pContext = NULL;
    ALCdevice *pDevice = NULL;
    ALint i;
    ALboolean bReturn = AL_FALSE;

    pDeviceList = new ALDeviceList();
    if ((pDeviceList) && (pDeviceList->GetNumDevices()))
    {
        ALFWprintf("\nSelect OpenAL Device:\n");
        for (i = 0; i < pDeviceList->GetNumDevices(); i++) 
            ALFWprintf("%d. %s%s\n", i + 1, pDeviceList->GetDeviceName(i), i == pDeviceList->GetDefaultDevice() ? "(DEFAULT)" : "");
    
        do {
            ALchar ch = _getch();
            i = atoi(&ch);
        } while ((i < 1) || (i > pDeviceList->GetNumDevices()));

        pDevice = alcOpenDevice(pDeviceList->GetDeviceName(i - 1));
        if (pDevice)
        {
            pContext = alcCreateContext(pDevice, NULL);
            if (pContext)
            {
                ALFWprintf("\nOpened %s Device\n", alcGetString(pDevice, ALC_DEVICE_SPECIFIER));
                alcMakeContextCurrent(pContext);
                bReturn = AL_TRUE;
            }
            else
            {
                alcCloseDevice(pDevice);
            }
        }

        delete pDeviceList;
        */

        this->context = context;
        this->device = device;
    }

    AudioDevice::~AudioDevice()
    {
        /*
        alcDestroyContext(reinterpret_cast<ALCcontext*>(context));
        alcCloseDevice(reinterpret_cast<ALCdevice*>(device));
        */
    }

    float AudioDevice::GetDurationByChars(const char* /*uri*/) const
    {
        return 0.0f;
    }
}

#endif