#include <Bibim/PCH.h>
#include <Bibim/Lock.Windows.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

    namespace Bibim
    {
        Lock::Lock()
        {
            ::InitializeCriticalSection(&cs);
        }

        Lock::~Lock()
        {
            ::DeleteCriticalSection(&cs);
        }

        void Lock::Acquire()
        {
            ::EnterCriticalSection(&cs);
        }

        void Lock::Unacquire()
        {
            ::LeaveCriticalSection(&cs);
        }

        bool Lock::TryAcquire()
        {
            return ::TryEnterCriticalSection(&cs) != FALSE;
        }

    }

#endif