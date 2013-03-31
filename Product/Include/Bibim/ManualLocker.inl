﻿namespace Bibim
{
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