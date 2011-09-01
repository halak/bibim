#pragma once
#ifndef __BIBIM_WEAKPOINTER_H__
#define __BIBIM_WEAKPOINTER_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/SharedPointer.h>

    namespace Bibim
    {
        template <typename T> class WeakPointer;
        template <typename T> class SharedPointer;

        template <typename T> class WeakPointer
        {
            public:
                typedef T PointeeType;

            public:
                inline WeakPointer();
                inline WeakPointer(const SharedPointer<T>& pointer);
                inline WeakPointer(const WeakPointer<T>& original);
                inline ~WeakPointer();

                inline void Reset();
                inline void Reset(const WeakPointer<T>& right);
                inline void Reset(const SharedPointer<T>& right);

                inline SharedPointer<T> Lock() const;

                inline bool IsAlive() const;

                inline WeakPointer<T>& operator = (const WeakPointer<T>& right);
                inline WeakPointer<T>& operator = (const SharedPointer<T>& right);

                inline bool operator == (const WeakPointer<T>& right) const;
                inline bool operator == (const SharedPointer<T>& right) const;
                inline bool operator == (T* right) const;
                inline bool operator != (const WeakPointer<T>& right) const;
                inline bool operator != (const SharedPointer<T>& right) const;
                inline bool operator != (T* right) const;

                inline operator T* () const;
                inline operator SharedPointer<T> () const;

                template <typename U> operator WeakPointer<U>() const
                {
                    return WeakPointer<U>(static_cast<U*>(pointee), life);
                }

            private:
                inline WeakPointer(T* pointee, SharedObjectLife* life);

            private:
                T* pointee;
                SharedObjectLife* life;

                template <typename U> friend class WeakPointer;
                template <typename To, typename From> friend WeakPointer<To> StaticCast(const WeakPointer<From>& from);
                template <typename To, typename From> friend WeakPointer<To> DynamicCast(const WeakPointer<From>& from);
        };
    }

#   include <Bibim/WeakPointer.inl>

#endif