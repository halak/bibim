#pragma once
#ifndef __BIBIM_VECTOR2_H__
#define __BIBIM_VECTOR2_H__

#   include <Bibim/Foundation.h>

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

            float Normalize();
            void Rotate(float rotation);
            void Rotate(float sin, float cos);
            float GetLength() const;
            float GetLengthSquared() const;

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

        template <> inline float Vector2::Get<0>(Vector2 value) { return value.X; }
        template <> inline float Vector2::Get<1>(Vector2 value) { return value.Y; }

        template <> inline void Vector2::Set<0>(Vector2& o, float value) { o.X = value; }
        template <> inline void Vector2::Set<1>(Vector2& o, float value) { o.Y = value; }

        template <> inline void Vector2::Add<0>(Vector2& o, float value) { o.X += value; }
        template <> inline void Vector2::Add<1>(Vector2& o, float value) { o.Y += value; }
    }

#   include <Bibim/Vector2.inl>

#endif