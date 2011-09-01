#pragma once
#ifndef __BIBIM_RANGE_H__
#define __BIBIM_RANGE_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        template <typename T> struct Range
        {
            typedef T ElementType;

            T Min;
            T Max;

            inline Range();
            inline Range(T min, T max);
            inline Range(const Range<T>& original);

            inline Range& operator = (const Range& right);
            inline bool operator == (const Range& right) const;
            inline bool operator != (const Range& right) const;
        };
    }

#   include <Bibim/Range.inl>

#endif