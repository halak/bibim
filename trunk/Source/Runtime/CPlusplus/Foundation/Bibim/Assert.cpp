#include <Bibim/PCH.h>
#include <Bibim/Assert.h>
#include <Bibim/Log.h>

namespace Bibim
{
    // TODO: Platform�� �°� �˷��ֵ��� �մϴ�.
    void Assert(const char* expression, const char* /*filename*/, int /*line*/)
    {
        Log::Error(expression);

        __asm int 3
    }
}