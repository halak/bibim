#pragma once
#ifndef __BIBIM_ASSERT_H__
#define __BIBIM_ASSERT_H__

#include <Bibim/Foundation.h>
#include <cassert>

namespace Bibim
{
#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       define BBBreak() { assert(false && "break"); }
#   else
#       define BBBreak() { }
#   endif

    /// Run-time�� ���� ���Ͽ� ���� ������ ��� �˷��ݴϴ�.
#   if (defined(BIBIM_PLATFORM_APPLE))
#       define BBAssert(exp)  // DO NOTHING
#   else
#       define BBAssert(exp)  assert(exp)
#   endif

    /// Compile-time�� ���� ���Ͽ� ���� ������ ��� �˷��ݴϴ�.
    /// ���� �迭 ũ�⳪ ��� �˻� �̿��մϴ�.
#   define BBStaticAssert(exp) { char StaticAssertion[(exp) ? 1 : 0]; StaticAssertion[0] = '\0'; }

#   if (defined(BIBIM_DEBUG))
        /// Debug ���¿����� �۵��ϴ� ASSERT
#       define BBAssertDebug(exp)  BBAssert(exp)
#   else
#       define BBAssertDebug(exp)
#   endif
}

#endif
