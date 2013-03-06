#pragma once
#ifndef __BIBIM_ASSERT_H__
#define __BIBIM_ASSERT_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
#       if (defined(BIBIM_PLATFORM_WINDOWS))
#           define BBBreak() { __asm int 3 }
#       else
#           define BBBreak() { }
#       endif

        /// Run-time에 식을 평가하여 식이 거짓일 경우 알려줍니다.
#       define BBAssert(exp) if (!(exp)) { Bibim::Assert(#exp, __FILE__, __LINE__); }

        /// Compile-time에 식을 평가하여 식이 거짓일 경우 알려줍니다.
        /// 고정 배열 크기나 상수 검사등에 이용합니다.
#       define BBStaticAssert(exp) { char StaticAssertion[(exp) ? 1 : 0]; StaticAssertion[0] = '\0'; }

#       if (defined(BIBIM_DEBUG))
            /// Debug 상태에서만 작동하는 ASSERT
#           define BBAssertDebug(exp) BBAssert(exp)
#       else
#           define BBAssertDebug(exp)
#       endif

        void Assert(const char* expression, const char* filename, int line);
    }

#endif