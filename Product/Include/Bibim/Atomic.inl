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
#       else
            variable++; // TODO
#       endif
    }

    void Atomic::Decrement(long& variable)
    {
#       if (defined(BIBIM_PLATFORM_WINDOWS))
            ::InterlockedDecrement(&variable);
#       else
            variable--; // TODO
#       endif
    }
}