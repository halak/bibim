#pragma once
#ifndef __BIBIM_VECTOR4_H__
#define __BIBIM_VECTOR4_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Vector3.h>

    namespace Bibim
    {
        struct Vector4
        {
            float X;
            float Y;
            float Z;
            float W;

            inline Vector4();
            inline Vector4(float x, float y, float z);
            inline Vector4(float x, float y, float z, float w);
            inline Vector4(const Vector3& original, float w);
            inline Vector4(const Vector4& original);

            inline Vector4  operator + () const;
            inline Vector4  operator - () const;

            inline Vector4& operator = (const Vector4& right);
            inline Vector4& operator += (const Vector4& right);
            inline Vector4& operator -= (const Vector4& right);
            inline Vector4& operator *= (float right);
            inline Vector4& operator /= (float right);
            inline Vector4  operator + (const Vector4& right) const;
            inline Vector4  operator - (const Vector4& right) const;
            inline Vector4  operator * (float right) const;
            inline Vector4  operator / (float right) const;
            
            inline bool operator == (const Vector4& right) const;
            inline bool operator != (const Vector4& right) const;

            inline friend Vector4 operator * (float left, const Vector4& right);

            static const Vector4 Zero;
            static const Vector4 UnitX;
            static const Vector4 UnitY;
            static const Vector4 UnitZ;
            static const Vector4 UnitW;
            static const Vector4 One;
        };
    }

#   include <Bibim/Vector4.inl>

#endif