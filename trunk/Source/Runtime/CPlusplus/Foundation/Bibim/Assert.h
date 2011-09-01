#pragma once
#ifndef __BIBIM_ASSERT_H__
#define __BIBIM_ASSERT_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        /// Run-time�� ���� ���Ͽ� ���� ������ ��� �˷��ݴϴ�.
#       define BBAssert(exp) if (!(exp)) { Bibim::Assert(#exp, __FILE__, __LINE__); }

        /// Compile-time�� ���� ���Ͽ� ���� ������ ��� �˷��ݴϴ�.
        /// ���� �迭 ũ�⳪ ��� �˻� �̿��մϴ�.
#       define BBStaticAssert(exp) { char StaticAssertion[(exp) ? 1 : 0]; StaticAssertion[0] = '\0'; }

#       if (defined(BIBIM_DEBUG))
            /// Debug ���¿����� �۵��ϴ� ASSERT
#           define BBAssertDebug(exp) BBAssert(exp)
#       else
#           define BBAssertDebug(exp)
#       endif

        void Assert(const char* expression, const char* filename, int line);
    }

#endif