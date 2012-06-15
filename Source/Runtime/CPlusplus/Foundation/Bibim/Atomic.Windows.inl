#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Bibim
{
    void Atomic::Increment(long& variable)
    {
        ::InterlockedIncrement(&variable);
    }

    void Atomic::Decrement(long& variable)
    {
        ::InterlockedDecrement(&variable);
    }
}