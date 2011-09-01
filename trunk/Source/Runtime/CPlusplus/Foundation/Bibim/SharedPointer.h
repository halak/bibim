#pragma once
#ifndef __BIBIM_SHAREDPOINTER_H__
#define __BIBIM_SHAREDPOINTER_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/SharedObjectLife.h>

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
                    : pointee(static_cast<T*>(pointee)),
                      life(pointee ? pointee->life : 0)
                {
                    if (pointee)
                    {
                        if (life == nullptr)
                        {
                            life = new SharedObjectLife(pointee);
                            pointee->life = life;
                        }

                        life->IncreaseStrongCount();
                    }
                }
                inline ~SharedPointer();

                inline void Reset();
                inline void Reset(const SharedPointer<T>& right);
                template <typename U> inline void Reset(U* right)
                {
                    if (pointee != right)
                    {
                        if (life)
                            life->DecreaseStrongCount();
                        
                        if (right && right->life == nullptr)
                            right->life = new SharedObjectLife(right);

                        pointee = static_cast<T*>(right);
                        life = right->life;

                        if (life)
                            life->IncreaseStrongCount();
                    }
                }

                inline void Swap(SharedPointer<T>& right);

                inline T* GetPointee() const;
                inline int GetReferenceCount() const;
                inline int GetWeakReferenceCount() const;

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
                    return SharedPointer<U>(static_cast<U*>(pointee), life);
                }

            private:
                inline SharedPointer(T* pointee, SharedObjectLife* life);

            private:
                T* pointee;
                SharedObjectLife* life;

                template <typename U> friend class SharedPointer;
                template <typename T> friend class WeakPointer;
                template <typename To, typename From> friend SharedPointer<To> StaticCast(const SharedPointer<From>& from);
                template <typename To, typename From> friend SharedPointer<To> DynamicCast(const SharedPointer<From>& from);
                friend class SharedObject;
        };
    }

#   include <Bibim/SharedPointer.inl>

#endif