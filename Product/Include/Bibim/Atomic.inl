#if defined(BIBIM_PLATFORM_WINDOWS)
#   ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#   endif
#   include <windows.h>
#endif

namespace Bibim
{
    void Atomic::Increment(long& variable)
    {
#       if (defined(BIBIM_PLATFORM_WINDOWS))
            ::InterlockedIncrement(&variable);
#       elif (defined(BIBIM_COMPILER_GCC))
            __sync_fetch_and_add(&variable, 1);
#       else
            variable++;
#       endif
    }

    void Atomic::Decrement(long& variable)
    {
#       if (defined(BIBIM_PLATFORM_WINDOWS))
            ::InterlockedDecrement(&variable);
#       elif (defined(BIBIM_COMPILER_GCC))
            __sync_fetch_and_sub(&variable, 1);
#       else
            variable--;
#       endif
    }
}