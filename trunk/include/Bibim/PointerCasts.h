#pragma once
#ifndef __BIBIM_POINTERCASTS_H__
#define __BIBIM_POINTERCASTS_H__

#include <Bibim/Foundation.h>
#include <Bibim/NullPointer.h>
#include <Bibim/SharedObject.h>

namespace Bibim
{
    /// @brief Raw-pointer가 가리키는 형식을 입력한 형식으로 변환합니다.
    /// @tparam To   변환할 형식
    /// @tparam From 변환할 Raw-pointer의 형식 (보통 인자에 의하여 자동 추론됩니다)
    /// @param  from 변환할 Raw-pointer
    /// @sa C++ static_cast
    template <typename To, typename From> inline To* StaticCast(From* from)
    {
        return static_cast<To*>(from);
    }

    /// Shared-pointer가 가리키는 형식을 지정한 형식(To)으로 변환합니다.
    /// 기존 C++ 표준 static_cast로는 불편한 Smart-pointer 변환을 편리하게 수행할 수 있도록 합니다.
    template <typename To, typename From> inline SharedPointer<To> StaticCast(const SharedPointer<From>& from)
    {
        return SharedPointer<To>(static_cast<To*>(from.pointee));
    }

    /// Raw-pointer가 가리키는 형식을 지정한 형식(To)으로 변환합니다.
    /// C++ 표준 dynamic_cast와 같습니다.
    template <typename To, typename From> inline To* DynamicCast(From* from)
    {
        return dynamic_cast<To*>(from);
    }

    /// Shared-pointer가 가리키는 형식을 지정한 형식(To)으로 변환합니다.
    /// 기존 C++ 표준 dynamic_cast로는 불편한 Smart-pointer 변환을 편리하게 수행할 수 있도록 합니다.
    template <typename To, typename From> inline SharedPointer<To> DynamicCast(const SharedPointer<From>& from)
    {
        return SharedPointer<To>(dynamic_cast<To*>(from.pointee));
    }
}

#endif