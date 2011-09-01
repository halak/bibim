#pragma once
#ifndef __BIBIM_CLONINGCONTEXT_H__
#define __BIBIM_CLONINGCONTEXT_H__

#   include <Bibim/FWD.h>
#   include <map>

    namespace Bibim
    {
        class CloningContext
        {
            public:
                CloningContext();
                ~CloningContext();

                template <typename T> inline T* Clone(T* original);
                template <typename T> inline T* CloneOrNull(T* original);
                template <typename T> inline SharedPointer<T> Clone(SharedPointer<T> original);
                template <typename T> inline SharedPointer<T> CloneOrNull(SharedPointer<T> original);
                template <typename T> inline WeakPointer<T> Clone(WeakPointer<T> original);
                template <typename T> inline WeakPointer<T> CloneOrNull(WeakPointer<T> original);

            private:
                template <typename T> inline T* CloneActually(T* original, T* fallback);
                template <typename T> inline SharedPointer<T> CloneActually(SharedPointer<T> original, SharedPointer<T> fallback);

            private:
                std::map<ICloneable*, ICloneable*> clones;
                std::map<ICloneablePtr, ICloneablePtr> sharedClones;
        };
    }

#   include <Bibim/CloningContext.inl>

#endif