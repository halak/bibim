#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_UNIX))

#include <Bibim/Lock.Unix.h>

namespace Bibim
{
    Lock::Lock()
    {
        pthread_mutex_init(&mutex, NULL);
    }

    Lock::~Lock()
    {
        pthread_mutex_destroy(&mutex);
    }

    void Lock::Acquire()
    {
        pthread_mutex_lock(&mutex);
    }

    void Lock::Unacquire()
    {
        pthread_mutex_unlock(&mutex);
    }

    bool Lock::TryAcquire()
    {
        return pthread_mutex_trylock(&mutex) == 0;
    }

}

#endif