namespace Bibim
{
    SharedObjectLife::SharedObjectLife(SharedObject* pointee)
        : pointee(pointee),
          strong(0),
          weak(0)
    {
    }

    int SharedObjectLife::GetStrong() const
    {
        return static_cast<int>(strong);
    }

    int SharedObjectLife::GetWeak() const
    {
        return static_cast<int>(weak);
    }

    bool SharedObjectLife::IsAlive() const
    {
        return strong != 0;
    }
}