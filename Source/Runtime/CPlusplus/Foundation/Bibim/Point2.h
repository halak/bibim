#pragma once
#ifndef __BIBIM_POINT2_H__
#define __BIBIM_POINT2_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        struct Point2
        {
            int X;
            int Y;

            inline Point2();
            inline Point2(int x, int y);
            inline Point2(const Point2& original);

            inline Point2& operator = (const Point2& right);
            inline Point2& operator += (const Point2& right);
            inline Point2& operator -= (const Point2& right);

            inline Point2 operator + (const Point2& right) const;
            inline Point2 operator - (const Point2& right) const;

            inline bool operator == (const Point2& right) const;
            inline bool operator != (const Point2& right) const;

            static const Point2 Zero;
        };
    }

#   include <Bibim/Point2.inl>

#endif