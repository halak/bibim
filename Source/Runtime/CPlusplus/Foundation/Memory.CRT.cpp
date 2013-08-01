#include <Bibim/PCH.h>
#include <Bibim/Memory.h>
#include <Bibim/Assert.h>
#include <memory.h>

namespace Bibim
{
    void Memory::Fill(void* destination, int destinationLength)
    {
        memset(destination, 0, destinationLength);
    }

    void Memory::Copy(void* destination, int destinationLength, const void* source, int sourceLength)
    {
        BBAssert(destinationLength >= sourceLength);
        memcpy(destination, source, sourceLength);
    }
}