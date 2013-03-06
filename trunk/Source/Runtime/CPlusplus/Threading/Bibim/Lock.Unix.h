#pragma once
#ifndef __BIBIM_LOCK_UNIX_H__
#define __BIBIM_LOCK_UNIX_H__

#   include <Bibim/FWD.h>

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
                friend class AutoLocker;
                friend class ManualLocker;
        };
    }

#endif