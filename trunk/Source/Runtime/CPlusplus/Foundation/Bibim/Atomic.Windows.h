#pragma once
#ifndef __BIBIM_ATOMIC_WINDOWS_H__
#define __BIBIM_ATOMIC_WINDOWS_H__

#   include <Bibim/FWD.h>

    namespace Bibim
    {
        class Atomic
        {
            BBThisIsStaticClass(Atomic);
            public:
                static inline void Increment(long& variable);
                static inline void Decrement(long& variable);
        };
    }

#   include <Bibim/Atomic.Windows.inl>

#endif