#pragma once
#ifndef __BIBIM_POINTERCASTS_H__
#define __BIBIM_POINTERCASTS_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/NullPointer.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/WeakPointer.h>

    namespace Bibim
    {
        /// Raw-pointer가 가리키는 형식을 지정한 형식(To)으로 변환합니다.
        /// C++ 표준 static_cast와 같습니다.
        template <typename To, typename From> inline To* StaticCast(From* from)
        {
            return static_cast<To*>(from);
        }

        /// Shared-pointer가 가리키는 형식을 지정한 형식(To)으로 변환합니다.
        /// 기존 C++ 표준 static_cast로는 불편한 Smart-pointer 변환을 편리하게 수행할 수 있도록 합니다.
        template <typename To, typename From> inline SharedPointer<To> StaticCast(const SharedPointer<From>& from)
        {
            return SharedPointer<To>(static_cast<To*>(from.pointee), from.life);
        }
        /// Weak-pointer가 가리키는 형식을 지정한 형식(To)으로 변환합니다.
        /// 기존 C++ 표준 static_cast로는 불편한 Smart-pointer 변환을 편리하게 수행할 수 있도록 합니다.
        template <typename To, typename From> inline WeakPointer<To> StaticCast(const WeakPointer<From>& from)
        {
            return WeakPointer<To>(static_cast<To*>(from.pointee), from.life);
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
            return SharedPointer<To>(dynamic_cast<To*>(from.pointee), from.life);
        }

        /// Weak-pointer가 가리키는 형식을 지정한 형식(To)으로 변환합니다.
        /// 기존 C++ 표준 dynamic_cast로는 불편한 Smart-pointer 변환을 편리하게 수행할 수 있도록 합니다.
        template <typename To, typename From> inline WeakPointer<To> DynamicCast(const WeakPointer<From>& from)
        {
            return WeakPointer<To>(dynamic_cast<To*>(from.pointee), from.life);
        }
    }

#endif