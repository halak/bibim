#pragma once
#ifndef __BIBIM_POINT_H__
#define __BIBIM_POINT_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        struct Point
        {
            int X;
            int Y;

            inline Point();
            inline Point(int x, int y);
            inline Point(const Point& original);

            inline Point& operator = (const Point& original);
            inline Point& operator += (const Point& right);
            inline Point& operator -= (const Point& right);

            inline Point operator + (const Point& right) const;
            inline Point operator - (const Point& right) const;

            inline bool operator == (const Point& right) const;
            inline bool operator != (const Point& right) const;

            static const Point Zero;
        };
    }

#   include <Bibim/Point.inl>

#endif