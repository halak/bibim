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
            inline Point2(float x, float y);
            inline Point2(const Point2& original);

            inline int Dot(Point2 right) const;

            inline Point2 operator + () const;
            inline Point2 operator - () const;

            inline Point2& operator = (const Point2& right);
            inline Point2& operator += (const Point2& right);
            inline Point2& operator -= (const Point2& right);
            inline Point2& operator *= (int right);
            inline Point2& operator /= (int right);

            inline Point2 operator + (const Point2& right) const;
            inline Point2 operator - (const Point2& right) const;
            inline Point2 operator * (int right) const;
            inline Point2 operator / (int right) const;

            inline bool operator == (const Point2& right) const;
            inline bool operator != (const Point2& right) const;

            static float GetDistance(Point2 a, Point2 b);
            static int GetDistanceSquared(Point2 a, Point2 b);

            static const Point2 Zero;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Point2::Point2()
            : X(0), Y(0)
        {
        }

        Point2::Point2(int x, int y)
            : X(x), Y(y)
        {
        }

        Point2::Point2(float x, float y)
            : X(static_cast<int>(x)), Y(static_cast<int>(y))
        {
        }

        Point2::Point2(const Point2& original)
            : X(original.X), Y(original.Y)
        {
        }

        int Point2::Dot(Point2 right) const
        {
            return (X * right.X) + (Y * right.Y);
        }

        Point2 Point2::operator + () const
        {
            return Point2(+X, +Y);
        }

        Point2 Point2::operator - () const
        {
            return Point2(-X, -Y);
        }

        Point2& Point2::operator = (const Point2& right)
        {
            X = right.X;
            Y = right.Y;
            return *this;
        }

        Point2& Point2::operator += (const Point2& right)
        {
            X += right.X;
            Y += right.Y;
            return *this;
        }

        Point2& Point2::operator -= (const Point2& right)
        {
            X -= right.X;
            Y -= right.Y;
            return *this;
        }

        Point2& Point2::operator *= (int right)
        {
            X *= right;
            Y *= right;
            return *this;
        }

        Point2& Point2::operator /= (int right)
        {
            X /= right;
            Y /= right;
            return *this;
        }

        Point2 Point2::operator + (const Point2& right) const
        {
            return Point2(X + right.X, Y + right.Y);
        }

        Point2 Point2::operator - (const Point2& right) const
        {
            return Point2(X - right.X, Y - right.Y);
        }

        Point2 Point2::operator * (int right) const
        {
            return Point2(X * right, Y * right);
        }

        Point2 Point2::operator / (int right) const
        {
            return Point2(X / right, Y / right);
        }

        bool Point2::operator == (const Point2& right) const
        {
            return X == right.X && Y == right.Y;
        }

        bool Point2::operator != (const Point2& right) const
        {
            return !operator == (right);
        }
    }

#endif