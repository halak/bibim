#include <Bibim/PCH.h>
#include <Bibim/Assert.h>
#include <Bibim/Log.h>

namespace Bibim
{
    // TODO: Platform에 맞게 알려주도록 합니다.
    void Assert(const char* expression, const char* /*filename*/, int /*line*/)
    {
        Log::Error(expression);

#       if (defined(BIBIM_PLATFORM_WINDOWS))
        __asm int 3
#       endif
    }
}