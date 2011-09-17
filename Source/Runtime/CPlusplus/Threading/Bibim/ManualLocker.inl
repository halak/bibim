namespace Bibim
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

    void ManualLocker::Unlock()
    {
        lockCount--;
        lock.Unacquire();
    }
}