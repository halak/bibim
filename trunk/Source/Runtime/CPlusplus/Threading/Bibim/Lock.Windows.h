#pragma once
#ifndef __BIBIM_LOCK_WINDOWS_H__
#define __BIBIM_LOCK_WINDOWS_H__

#   include <Bibim/FWD.h>

#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>

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
                CRITICAL_SECTION cs;

                friend class AutoLocker;
                friend class ManualLocker;
        };
    }

#endif