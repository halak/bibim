#pragma once
#ifndef __BIBIM_POINTERCASTS_H__
#define __BIBIM_POINTERCASTS_H__

#include <Bibim/Foundation.h>
#include <Bibim/NullPointer.h>
#include <Bibim/SharedObject.h>

namespace Bibim
{
    /// @brief Raw-pointer�� ����Ű�� ������ �Է��� �������� ��ȯ�մϴ�.
    /// @tparam To   ��ȯ�� ����
    /// @tparam From ��ȯ�� Raw-pointer�� ���� (���� ���ڿ� ���Ͽ� �ڵ� �߷е˴ϴ�)
    /// @param  from ��ȯ�� Raw-pointer
    /// @sa C++ static_cast
    template <typename To, typename From> inline To* StaticCast(From* from)
    {
        return static_cast<To*>(from);
    }

    /// Shared-pointer�� ����Ű�� ������ ������ ����(To)���� ��ȯ�մϴ�.
    /// ���� C++ ǥ�� static_cast�δ� ������ Smart-pointer ��ȯ�� ���ϰ� ������ �� �ֵ��� �մϴ�.
    template <typename To, typename From> inline SharedPointer<To> StaticCast(const SharedPointer<From>& from)
    {
        return SharedPointer<To>(static_cast<To*>(from.pointee));
    }

    /// Raw-pointer�� ����Ű�� ������ ������ ����(To)���� ��ȯ�մϴ�.
    /// C++ ǥ�� dynamic_cast�� �����ϴ�.
    template <typename To, typename From> inline To* DynamicCast(From* from)
    {
        return dynamic_cast<To*>(from);
    }

    /// Shared-pointer�� ����Ű�� ������ ������ ����(To)���� ��ȯ�մϴ�.
    /// ���� C++ ǥ�� dynamic_cast�δ� ������ Smart-pointer ��ȯ�� ���ϰ� ������ �� �ֵ��� �մϴ�.
    template <typename To, typename From> inline SharedPointer<To> DynamicCast(const SharedPointer<From>& from)
    {
        return SharedPointer<To>(dynamic_cast<To*>(from.pointee));
    }
}

#endif