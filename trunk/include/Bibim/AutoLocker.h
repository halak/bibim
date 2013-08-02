#pragma once
#ifndef __BIBIM_AUTOLOCKER_H__
#define __BIBIM_AUTOLOCKER_H__

#include <Bibim/FWD.h>
#include <Bibim/Lock.h>

namespace Bibim
{
    class AutoLocker
    {
        BBThisIsNoncopyableClass(AutoLocker);
        public:
            inline AutoLocker(Lock& lock);
            inline ~AutoLocker();
        
        private:
            Lock& lock;
    };

#   define BBAutoLock(lock) Bibim::AutoLocker lock##Locker(lock);

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    AutoLocker::AutoLocker(Lock& lock)
        : lock(lock)
    {
        lock.Acquire();
    }

    AutoLocker::~AutoLocker()
    {
        lock.Unacquire();
    }
}

#endif