#pragma once
#ifndef __BIBIM_VECTOR3_H__
#define __BIBIM_VECTOR3_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        struct Vector3
        {
            float X;
            float Y;
            float Z;

            inline Vector3();
            inline Vector3(int x, int y, int z);
            inline Vector3(float x, float y, float z);
            inline Vector3(Vector2 xy, float z);
            inline Vector3(const Vector3& original);

            inline float   Dot(Vector3 right) const;
            inline Vector3 Cross(Vector3 right) const;

            float Normalize();
            float GetLength() const;

            inline Vector3  operator + () const;
            inline Vector3  operator - () const;

            inline Vector3& operator = (const Vector3& right);
            inline Vector3& operator += (const Vector3& right);
            inline Vector3& operator -= (const Vector3& right);
            inline Vector3& operator *= (float right);
            inline Vector3& operator /= (float right);
            inline Vector3  operator + (const Vector3& right) const;
            inline Vector3  operator - (const Vector3& right) const;
            inline Vector3  operator * (float right) const;
            inline Vector3  operator / (float right) const;

            inline bool operator == (const Vector3& right) const;
            inline bool operator != (const Vector3& right) const;

            static float GetDistance(Vector3 a, Vector3 b);
            static float GetDistanceSquared(Vector3 a, Vector3 b);

            inline friend Vector3 operator * (float left, const Vector3& right);

            static const Vector3 Zero;
            static const Vector3 UnitX;
            static const Vector3 UnitY;
            static const Vector3 UnitZ;
            static const Vector3 One;
            static const Vector3 Minimum;
            static const Vector3 Maximum;
        };
    }

#   include <Bibim/Vector3.inl>

#endif