#include <Bibim/PCH.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    // TODO: Platform�� �°� �˷��ֵ��� �մϴ�.
    void Assert(const char* /*expression*/, const char* /*filename*/, int /*line*/)
    {
        __asm int 3
    }
}