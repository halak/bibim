namespace Bibim
{
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