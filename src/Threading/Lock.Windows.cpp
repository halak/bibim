#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_WINDOWS))

#include <Bibim/Lock.Windows.h>

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