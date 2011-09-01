namespace Bibim
{
    template <typename T> SharedPointer<T>::SharedPointer()
        : pointee(0),
          life(0)
    {
    }

    template <typename T> SharedPointer<T>::SharedPointer(T* pointee, SharedObjectLife* life)
        : pointee(pointee),
          life(pointee ? life : 0)
    {
        if (this->life)
            this->life->IncreaseStrongCount();
    }

    template <typename T> SharedPointer<T>::SharedPointer(const SharedPointer<T>& original)
        : pointee(original.pointee),
          life(original.life)
    {
        if (life)
            life->IncreaseStrongCount();
    }

    template <typename T> SharedPointer<T>::~SharedPointer()
    {
        if (life)
            life->DecreaseStrongCount();
    }

    template <typename T> void SharedPointer<T>::Reset()
    {
        if (life)
            life->DecreaseStrongCount();

        pointee = 0;
        life = 0;
    }

    template <typename T> void SharedPointer<T>::Reset(const SharedPointer<T>& right)
    {
        if (this == &right)
            return;

        if (life)
            life->DecreaseStrongCount();

        pointee = right.pointee;
        life = right.life;

        if (life)
            life->IncreaseStrongCount();
    }

    template <typename T> void SharedPointer<T>::Swap(SharedPointer<T>& right)
    {
        T* temporaryPointee = pointee;
        SharedObjectLife* temporarySharedObjectLife = life;

        pointee = right.pointee;
        life = right.life;

        right.pointee = temporaryPointee;
        right.life = temporarySharedObjectLife;
    }

    template <typename T> T* SharedPointer<T>::GetPointee() const
    {
        return pointee;
    }

    template <typename T> int SharedPointer<T>::GetReferenceCount() const
    {
        if (life)
            return life->GetStrong();
        else
            return 0;
    }

    template <typename T> int SharedPointer<T>::GetWeakReferenceCount() const
    {
        if (life)
            return life->GetWeak();
        else
            return 0;
    }

    template <typename T> SharedPointer<T>& SharedPointer<T>::operator = (const SharedPointer<T>& right)
    {
        Reset(right);
        return *this;
    }

    template <typename T> bool SharedPointer<T>::operator == (const SharedPointer<T>& right) const
    {
        return pointee == right.pointee;
    }

    template <typename T> bool SharedPointer<T>::operator != (const SharedPointer<T>& right) const
    {
        return !operator == (right);
    }

    template <typename T> SharedPointer<T>::operator T* () const
    {
        return pointee;
    }

    template <typename T> T& SharedPointer<T>::operator * () const
    {
        return *pointee;
    }

    template <typename T> T* SharedPointer<T>::operator -> () const
    {
        return pointee;
    }
}