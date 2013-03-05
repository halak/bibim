#include <Bibim/PCH.h>
#include <Bibim/Memory.h>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace Bibim
{
    void Memory::Fill(void* destination, int destinationLength)
    {
        ::ZeroMemory(destination, destinationLength);
    }

    void Memory::Copy(void* destination, int destinationLength, const void* source, int sourceLength)
    {
        ::memcpy_s(destination, destinationLength, source, sourceLength);
    }
}