#pragma once
#ifndef __BIBIM_MANUALLOCKER_H__
#define __BIBIM_MANUALLOCKER_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Lock.h>

    namespace Bibim
    {
        class ManualLocker
        {
            BBThisIsNoncopyableClass(ManualLocker);
            public:
                inline ManualLocker(Bibim::Lock& lock);
                ~ManualLocker();

                inline void Lock();
                inline bool TryLock();
                inline void Unlock();

            private:
                Bibim::Lock& lock;
                int lockCount;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        ManualLocker::ManualLocker(Bibim::Lock& lock)
            : lock(lock),
              lockCount(0)
        {
        }

        void ManualLocker::Lock()
        {
            lock.Acquire();
            lockCount++;
        }

        bool ManualLocker::TryLock()
        {
            if (lock.TryAcquire())
            {
                lockCount++;
                return true;
            }
            else
                return false;
        }

        void ManualLocker::Unlock()
        {
            lockCount--;
            lock.Unacquire();
        }
    }

#endif