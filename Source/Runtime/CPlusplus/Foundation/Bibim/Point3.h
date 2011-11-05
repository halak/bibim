#pragma once
#ifndef __BIBIM_POINT3_H__
#define __BIBIM_POINT3_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        struct Point3
        {
            int X;
            int Y;
            int Z;

            inline Point3();
            inline Point3(int x, int y, int z);
            inline Point3(const Point3& original);

            inline Point3& operator = (const Point3& right);
            inline Point3& operator += (const Point3& right);
            inline Point3& operator -= (const Point3& right);

            inline Point3 operator + (const Point3& right) const;
            inline Point3 operator - (const Point3& right) const;

            inline bool operator == (const Point3& right) const;
            inline bool operator != (const Point3& right) const;

            static const Point3 Zero;
        };
    }

#   include <Bibim/Point3.inl>

#endif