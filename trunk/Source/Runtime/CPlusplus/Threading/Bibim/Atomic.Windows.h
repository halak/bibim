#pragma once
#ifndef __BIBIM_ATOMIC_WINDOWS_H__
#define __BIBIM_ATOMIC_WINDOWS_H__

#   include <Bibim/FWD.h>

#   if (defined(BIBIM_PLATFORM_WINDOWS))

        namespace Bibim
        {
            class Atomic
            {
                BBThisIsStaticClass(Atomic);
                public:
                    void Exchange(long& variable, long value);
            };
        }

#   endif

#endif