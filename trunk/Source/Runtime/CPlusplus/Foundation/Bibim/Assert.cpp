#include <Bibim/PCH.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    // TODO: Platform에 맞게 알려주도록 합니다.
    void Assert(const char* /*expression*/, const char* /*filename*/, int /*line*/)
    {
        __asm int 3
    }
}