#pragma once
#ifndef __BIBIM_LOCK_UNIX_H__
#define __BIBIM_LOCK_UNIX_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_PLATFORM_UNIX))

#include <pthread.h>

namespace Bibim
{
    class Lock
    {
        BBThisIsNoncopyableClass(Lock);
        public:
            Lock();
            ~Lock();

        private:
            void Acquire();
            void Unacquire();
            bool TryAcquire();

        private:
            mutable pthread_mutex_t mutex;

            friend class AutoLocker;
            friend class ManualLocker;
    };
}

#endif
#endif