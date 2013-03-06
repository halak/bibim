#include <Bibim/PCH.h>
#include <Bibim/Memory.h>
#include <cstring>

namespace Bibim
{
    void Memory::Fill(void* destination, int destinationLength)
    {
        std::memset(destination, 0, destinationLength);
    }

    void Memory::Copy(void* destination, int destinationLength, const void* source, int sourceLength)
    {
#       if (defined(BIBIM_PLATFORM_WINDOWS))
            ::memcpy_s(destination, destinationLength, source, sourceLength);
#       else
            destinationLength; // unused
            std::memcpy(destination, source, sourceLength);
#       endif
    }
}