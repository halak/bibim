#pragma once
#ifndef __BIBIM_SHAREDPOINTER_H__
#define __BIBIM_SHAREDPOINTER_H__

#include <Bibim/Foundation.h>
#include <Bibim/SharedObject.h>

namespace Bibim
{
    template <typename T> class SharedPointer
    {
        public:
            typedef T PointeeType;

        public:
            inline SharedPointer();
            inline SharedPointer(const SharedPointer<T>& original);
            template <typename U> inline SharedPointer(U* pointee)
                : pointee(static_cast<T*>(pointee))
            {
                if (pointee)
                    pointee->IncreaseReferenceCount();
            }
#           if (defined(BIBIM_CPLUSPLUS_0X))
            inline SharedPointer(std::nullptr_t n)
                : pointee(0)
            {
                n = n;
            }
#           endif
            inline ~SharedPointer();

            inline void Reset();
            inline void Reset(const SharedPointer<T>& right);
            template <typename U> inline void Reset(U* right)
            {
                if (pointee != right)
                {
                    T* oldPointee = pointee;

                    pointee = static_cast<T*>(right);

                    if (oldPointee)
                        oldPointee->DecreaseReferenceCount();

                    if (pointee)
                        pointee->IncreaseReferenceCount();
                }
            }

            inline void Swap(SharedPointer<T>& right);

            inline T* GetPointee() const;
            inline int GetReferenceCount() const;

            inline SharedPointer<T>& operator = (const SharedPointer<T>& right);

            inline bool operator == (const SharedPointer<T>& right) const;
            inline bool operator != (const SharedPointer<T>& right) const;
            template <typename U> bool operator == (U* right) const
            {
                return pointee == right;
            }
            template <typename U> bool operator != (U* right) const
            {
                return pointee != right;
            }
#           if (defined(BIBIM_CPLUSPLUS_0X))
            bool operator == (std::nullptr_t) const
            {
                return pointee == 0;
            }
            bool operator != (std::nullptr_t) const
            {
                return pointee != 0;
            }
#           endif

            inline operator T* () const;
            inline T& operator * () const;
            inline T* operator -> () const;

            template <typename U> operator SharedPointer<U>() const
            {
                return SharedPointer<U>(static_cast<U*>(pointee));
            }

        private:
            T* pointee;

            template <typename U> friend class SharedPointer;
            template <typename To, typename From> friend SharedPointer<To> StaticCast(const SharedPointer<From>& from);
            template <typename To, typename From> friend SharedPointer<To> DynamicCast(const SharedPointer<From>& from);
            friend class SharedObject;
    };

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

#endif