namespace Bibim
{
    template <typename T> SharedPointer<T>::SharedPointer()
        : pointee(0)
    {
    }

    template <typename T> SharedPointer<T>::SharedPointer(const SharedPointer<T>& original)
        : pointee(original.pointee)
    {
        if (pointee)
            pointee->IncreaseReferenceCount();
    }

    template <typename T> SharedPointer<T>::~SharedPointer()
    {
        if (pointee)
            pointee->DecreaseReferenceCount();
    }

    template <typename T> void SharedPointer<T>::Reset()
    {
        T* oldPointee = pointee;
        pointee = 0;

        if (oldPointee)
            oldPointee->DecreaseReferenceCount();
    }

    template <typename T> void SharedPointer<T>::Reset(const SharedPointer<T>& right)
    {
        if (this == &right)
            return;

        if (right.pointee)
            right.pointee->IncreaseReferenceCount();

        T* oldPointee = pointee;
        pointee = right.pointee;

        if (oldPointee)
            oldPointee->DecreaseReferenceCount();
    }

    template <typename T> void SharedPointer<T>::Swap(SharedPointer<T>& right)
    {
        T* temporaryPointee = pointee;
        pointee = right.pointee;
        right.pointee = temporaryPointee;
    }

    template <typename T> T* SharedPointer<T>::GetPointee() const
    {
        return pointee;
    }

    template <typename T> int SharedPointer<T>::GetReferenceCount() const
    {
        if (pointee)
            return static_cast<int>(pointee->referenceCount);
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