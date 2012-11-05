﻿#pragma once
#ifndef __BIBIM_SHAREDPOINTER_H__
#define __BIBIM_SHAREDPOINTER_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/SharedObject.h>

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
    }

#   include <Bibim/SharedPointer.inl>

#endif