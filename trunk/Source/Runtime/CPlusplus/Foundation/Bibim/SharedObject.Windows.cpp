#include <Bibim/PCH.h>
#include <Bibim/SharedObject.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>

    namespace Bibim
    {
        void SharedObject::IncreaseReferenceCount()
        {
            InterlockedIncrement(&referenceCount);
        }

        void SharedObject::DecreaseReferenceCount()
        {
            InterlockedDecrement(&referenceCount);
            if (referenceCount == 0)
                delete this;
        }
    }

#endif