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

            inline Point3 operator + () const;
            inline Point3 operator - () const;

            inline Point3& operator = (const Point3& right);
            inline Point3& operator += (const Point3& right);
            inline Point3& operator -= (const Point3& right);
            inline Point3& operator *= (int right);
            inline Point3& operator /= (int right);

            inline Point3 operator + (const Point3& right) const;
            inline Point3 operator - (const Point3& right) const;
            inline Point3 operator * (int right) const;
            inline Point3 operator / (int right) const;

            inline bool operator == (const Point3& right) const;
            inline bool operator != (const Point3& right) const;

            static const Point3 Zero;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Point3::Point3()
            : X(0), Y(0), Z(0)
        {
        }

        Point3::Point3(int x, int y, int z)
            : X(x), Y(y), Z(z)
        {
        }

        Point3::Point3(const Point3& original)
            : X(original.X), Y(original.Y), Z(original.Z)
        {
        }

        Point3 Point3::operator + () const
        {
            return Point3(+X, +Y, +Z);
        }

        Point3 Point3::operator - () const
        {
            return Point3(-X, -Y, -Z);
        }

        Point3& Point3::operator = (const Point3& right)
        {
            X = right.X;
            Y = right.Y;
            Z = right.Z;
            return *this;
        }

        Point3& Point3::operator += (const Point3& right)
        {
            X += right.X;
            Y += right.Y;
            Z += right.Z;
            return *this;
        }

        Point3& Point3::operator -= (const Point3& right)
        {
            X -= right.X;
            Y -= right.Y;
            Z -= right.Z;
            return *this;
        }

        Point3& Point3::operator *= (int right)
        {
            X *= right;
            Y *= right;
            Z *= right;
            return *this;
        }

        Point3& Point3::operator /= (int right)
        {
            X /= right;
            Y /= right;
            Z /= right;
            return *this;
        }

        Point3 Point3::operator + (const Point3& right) const
        {
            return Point3(X + right.X, Y + right.Y, Z + right.Z);
        }

        Point3 Point3::operator - (const Point3& right) const
        {
            return Point3(X - right.X, Y - right.Y, Z - right.Z);
        }

        Point3 Point3::operator * (int right) const
        {
            return Point3(X * right, Y * right, Z * right);
        }

        Point3 Point3::operator / (int right) const
        {
            return Point3(X / right, Y / right, Z / right);
        }

        bool Point3::operator == (const Point3& right) const
        {
            return X == right.X && Y == right.Y && Z == right.Z;
        }

        bool Point3::operator != (const Point3& right) const
        {
            return !operator == (right);
        }
    }

#endif