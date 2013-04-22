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

            inline Point4 operator + () const;
            inline Point4 operator - () const;

            inline Point4& operator = (const Point4& right);
            inline Point4& operator += (const Point4& right);
            inline Point4& operator -= (const Point4& right);
            inline Point4& operator *= (int right);
            inline Point4& operator /= (int right);

            inline Point4 operator + (const Point4& right) const;
            inline Point4 operator - (const Point4& right) const;
            inline Point4 operator * (int right) const;
            inline Point4 operator / (int right) const;

            inline bool operator == (const Point4& right) const;
            inline bool operator != (const Point4& right) const;

            static const Point4 Zero;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Point4::Point4()
            : X(0), Y(0), Z(0), W(0)
        {
        }

        Point4::Point4(int x, int y, int z, int w)
            : X(x), Y(y), Z(z), W(w)
        {
        }

        Point4::Point4(const Point4& original)
            : X(original.X), Y(original.Y), Z(original.Z), W(original.W)
        {
        }

        Point4 Point4::operator + () const
        {
            return Point4(+X, +Y, +Z, +W);
        }

        Point4 Point4::operator - () const
        {
            return Point4(-X, -Y, -Z, -W);
        }

        Point4& Point4::operator = (const Point4& right)
        {
            X = right.X;
            Y = right.Y;
            Z = right.Z;
            W = right.W;
            return *this;
        }

        Point4& Point4::operator += (const Point4& right)
        {
            X += right.X;
            Y += right.Y;
            Z += right.Z;
            W += right.W;
            return *this;
        }

        Point4& Point4::operator -= (const Point4& right)
        {
            X -= right.X;
            Y -= right.Y;
            Z -= right.Z;
            W -= right.W;
            return *this;
        }

        Point4& Point4::operator *= (int right)
        {
            X *= right;
            Y *= right;
            Z *= right;
            W *= right;
            return *this;
        }

        Point4& Point4::operator /= (int right)
        {
            X /= right;
            Y /= right;
            Z /= right;
            W /= right;
            return *this;
        }

        Point4 Point4::operator + (const Point4& right) const
        {
            return Point4(X + right.X, Y + right.Y, Z + right.Z, W + right.W);
        }

        Point4 Point4::operator - (const Point4& right) const
        {
            return Point4(X - right.X, Y - right.Y, Z - right.Z, W - right.W);
        }

        Point4 Point4::operator * (int right) const
        {
            return Point4(X * right, Y * right, Z * right, W * right);
        }

        Point4 Point4::operator / (int right) const
        {
            return Point4(X / right, Y / right, Z / right, W / right);
        }

        bool Point4::operator == (const Point4& right) const
        {
            return X == right.X && Y == right.Y && Z == right.Z && W == right.W;
        }

        bool Point4::operator != (const Point4& right) const
        {
            return !operator == (right);
        }
    }

#endif