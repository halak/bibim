#include <Bibim/PCH.h>
#include <Bibim/SharedObjectLife.h>
#include <Bibim/SharedObject.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>

    namespace Bibim
    {
        void SharedObjectLife::IncreaseStrongCount()
        {
            InterlockedIncrement(&strong);
        }

        bool SharedObjectLife::DecreaseStrongCount()
        {
            InterlockedDecrement(&strong);
            if (strong == 0)
            {
                delete pointee;

                if (weak == 0)
                    delete this;

                return true;
            }
            else
                return false;
        }

        void SharedObjectLife::IncreaseWeakCount()
        {
            InterlockedIncrement(&weak);
        }

        void SharedObjectLife::DecreaseWeakCount()
        {
            InterlockedDecrement(&weak);
            if (strong == 0 && weak == 0)
                delete this;
        }
    }

#endif