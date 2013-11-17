#pragma once
#ifndef __BIBIM_VECTOR2_H__
#define __BIBIM_VECTOR2_H__

#include <Bibim/Foundation.h>

namespace Bibim
{
    struct Vector2
    {
        float X;
        float Y;

        inline Vector2();
        inline Vector2(int x, int y);
        inline Vector2(float x, float y);
        inline Vector2(const Vector2& original);
        
        inline float Dot(Vector2 right) const;
        inline Vector2 Multiply(Vector2 right) const;

        float Normalize();
        void Rotate(float rotation);
        void Rotate(float sin, float cos);
        void Reflect(Vector2 normal);
        float GetLength() const;
        inline float GetLengthSquared() const;

        float ToRadian() const;

        inline Vector2  operator + () const;
        inline Vector2  operator - () const;

        inline Vector2& operator = (const Vector2& right);
        inline Vector2& operator += (const Vector2& right);
        inline Vector2& operator -= (const Vector2& right);
        inline Vector2& operator *= (float right);
        inline Vector2& operator /= (float right);
        inline Vector2  operator + (const Vector2& right) const;
        inline Vector2  operator - (const Vector2& right) const;
        inline Vector2  operator * (float right) const;
        inline Vector2  operator / (float right) const;
        
        inline bool operator == (const Vector2& right) const;
        inline bool operator != (const Vector2& right) const;

        static float GetDistance(Vector2 a, Vector2 b);
        static float GetDistanceSquared(Vector2 a, Vector2 b);
        static bool IsCollinear(Vector2 a, Vector2 b, Vector2 c);

        inline friend Vector2 operator * (float left, const Vector2& right);

        static const Vector2 Zero;
        static const Vector2 UnitX;
        static const Vector2 UnitY;
        static const Vector2 One;
        static const Vector2 Minimum;
        static const Vector2 Maximum;

        template <int Index> inline static float Get(Vector2  value);
        template <int Index> inline static void  Set(Vector2& o, float value);
        template <int Index> inline static void  Add(Vector2& o, float value);
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2::Vector2()
        : X(0.0f), Y(0.0f)
    {
    }

    Vector2::Vector2(int x, int y)
        : X(static_cast<float>(x)), Y(static_cast<float>(y))
    {
    }

    Vector2::Vector2(float x, float y)
        : X(x), Y(y)
    {
    }

    Vector2::Vector2(const Vector2& original)
        : X(original.X), Y(original.Y)
    {
    }

    float Vector2::Dot(Vector2 right) const
    {
        return (X * right.X) + (Y * right.Y);
    }

    Vector2 Vector2::Multiply(Vector2 right) const
    {
        return Vector2(X * right.X, Y * right.Y);
    }

    float Vector2::GetLengthSquared() const
    {
        return (X * X) + (Y * Y);
    }

    Vector2 Vector2::operator + () const
    {
        return Vector2(+X, +Y);
    }

    Vector2 Vector2::operator - () const
    {
        return Vector2(-X, -Y);
    }

    Vector2& Vector2::operator = (const Vector2& right)
    {
        X = right.X;
        Y = right.Y;
        return *this;
    }

    Vector2& Vector2::operator += (const Vector2& right)
    {
        X += right.X;
        Y += right.Y;
        return *this;
    }

    Vector2& Vector2::operator -= (const Vector2& right)
    {
        X -= right.X;
        Y -= right.Y;
        return *this;
    }

    Vector2& Vector2::operator *= (float right)
    {
        X *= right;
        Y *= right;
        return *this;
    }

    Vector2& Vector2::operator /= (float right)
    {
        X /= right;
        Y /= right;
        return *this;
    }

    Vector2 Vector2::operator + (const Vector2& right) const
    {
        return Vector2(X + right.X, Y + right.Y);
    }

    Vector2 Vector2::operator - (const Vector2& right) const
    {
        return Vector2(X - right.X, Y - right.Y);
    }

    Vector2 Vector2::operator * (float right) const
    {
        return Vector2(X * right, Y * right);
    }

    Vector2 Vector2::operator / (float right) const
    {
        return Vector2(X / right, Y / right);
    }

    bool Vector2::operator == (const Vector2& right) const
    {
        return X == right.X && Y == right.Y;
    }

    bool Vector2::operator != (const Vector2& right) const
    {
        return !operator == (right);
    }

    Vector2 operator * (float left, const Vector2& right)
    {
        return Vector2(left * right.X, left * right.Y);
    }

    template <> inline float Vector2::Get<0>(Vector2 value) { return value.X; }
    template <> inline float Vector2::Get<1>(Vector2 value) { return value.Y; }

    template <> inline void Vector2::Set<0>(Vector2& o, float value) { o.X = value; }
    template <> inline void Vector2::Set<1>(Vector2& o, float value) { o.Y = value; }

    template <> inline void Vector2::Add<0>(Vector2& o, float value) { o.X += value; }
    template <> inline void Vector2::Add<1>(Vector2& o, float value) { o.Y += value; }
}

#endif