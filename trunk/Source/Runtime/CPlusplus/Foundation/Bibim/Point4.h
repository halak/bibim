#pragma once
#ifndef __BIBIM_POINT4_H__
#define __BIBIM_POINT4_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        struct Point4
        {
            int X;
            int Y;
            int Z;
            int W;

            inline Point4();
            inline Point4(int x, int y, int z, int w);
            inline Point4(const Point4& original);

            inline Point4& operator = (const Point4& right);
            inline Point4& operator += (const Point4& right);
            inline Point4& operator -= (const Point4& right);

            inline Point4 operator + (const Point4& right) const;
            inline Point4 operator - (const Point4& right) const;

            inline bool operator == (const Point4& right) const;
            inline bool operator != (const Point4& right) const;

            static const Point4 Zero;
        };
    }

#   include <Bibim/Point4.inl>

#endif