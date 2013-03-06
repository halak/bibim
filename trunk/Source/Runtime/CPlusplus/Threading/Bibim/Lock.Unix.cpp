#include <Bibim/PCH.h>
#include <Bibim/Lock.Unix.h>

namespace Bibim
{
    Lock::Lock()
    {
    }

    Lock::~Lock()
    {
    }

    void Lock::Acquire()
    {
    }

    void Lock::Unacquire()
    {
    }

    bool Lock::TryAcquire()
    {
        return false;
        // return ::TryEnterCriticalSection(&cs) != FALSE;
    }

}