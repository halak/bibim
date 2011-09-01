namespace Bibim
{
    template <typename T> WeakPointer<T>::WeakPointer()
        : pointee(0),
          life(0)
    {
    }

    template <typename T> WeakPointer<T>::WeakPointer(const SharedPointer<T>& pointer)
        : pointee(pointer),
          life(pointer ? pointer.life : 0)
    {
        if (life)
            life->IncreaseWeakCount();
    }

    template <typename T> WeakPointer<T>::WeakPointer(T* pointee, SharedObjectLife* life)
        : pointee(pointee),
          life(life)
    {
        if (life)
            life->IncreaseWeakCount();
    }

    template <typename T> WeakPointer<T>::WeakPointer(const WeakPointer<T>& original)
        : pointee(original.pointee),
          life(original.life)
    {
        if (life)
            life->IncreaseWeakCount();
    }

    template <typename T> WeakPointer<T>::~WeakPointer()
    {
        if (life)
            life->DecreaseWeakCount();
    }

    template <typename T> void WeakPointer<T>::Reset()
    {
        if (life)
            life->DecreaseWeakCount();

        pointee = 0;
        life = 0;
    }

    template <typename T> void WeakPointer<T>::Reset(const WeakPointer<T>& right)
    {
        if (life)
            life->DecreaseWeakCount();

        pointee = right.pointee;
        life = right.life;

        if (life)
            life->IncreaseWeakCount();
    }

    template <typename T> void WeakPointer<T>::Reset(const SharedPointer<T>& right)
    {
        if (life)
            life->DecreaseWeakCount();

        pointee = right.pointee;
        life = right.life;

        if (life)
            life->IncreaseWeakCount();
    }

    template <typename T> SharedPointer<T> WeakPointer<T>::Lock() const
    {
        if (life && life->IsAlive())
            return SharedPointer<T>(pointee, life);
        else
            return SharedPointer<T>(0, 0);
    }

    template <typename T> bool WeakPointer<T>::IsAlive() const
    {
        return life && life->IsAlive();
    }

    template <typename T> WeakPointer<T>& WeakPointer<T>::operator = (const WeakPointer<T>& right)
    {
        Reset(right);
        return *this;
    }

    template <typename T> WeakPointer<T>& WeakPointer<T>::operator = (const SharedPointer<T>& right)
    {
        Reset(right);
        return *this;
    }

    template <typename T> bool WeakPointer<T>::operator == (const WeakPointer<T>& right) const
    {
        if (IsAlive() == right.IsAlive())
            return pointee == right.pointee;
        else
            return false;
    }

    template <typename T> bool WeakPointer<T>::operator == (const SharedPointer<T>& right) const
    {
        if (IsAlive() != static_cast<bool>(right.GetPointee() != 0))
            return pointee == right.GetPointee();
        else
            return false;
    }

    template <typename T> bool WeakPointer<T>::operator == (T* right) const
    {
        if (IsAlive() != static_cast<bool>(right != 0))
            return pointee == right;
        else
            return false;
    }

    template <typename T> bool WeakPointer<T>::operator != (const WeakPointer<T>& right) const
    {
        return !operator == (right);
    }

    template <typename T> bool WeakPointer<T>::operator != (const SharedPointer<T>& right) const
    {
        return !operator == (right);
    }

    template <typename T> bool WeakPointer<T>::operator != (T* right) const
    {
        return !operator == (right);
    }

    template <typename T> WeakPointer<T>::operator T* () const
    {
        if (IsAlive())
            return pointee;
        else
            return 0;
    }

    template <typename T> WeakPointer<T>::operator SharedPointer<T> () const
    {
        return Lock();
    }
}