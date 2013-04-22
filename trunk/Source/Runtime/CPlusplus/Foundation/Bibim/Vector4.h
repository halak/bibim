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

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        Vector4::Vector4()
            : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f)
        {
        }

        Vector4::Vector4(float x, float y, float z)
            : X(x), Y(y), Z(z), W(0.0f)
        {
        }

        Vector4::Vector4(float x, float y, float z, float w)
            : X(x), Y(y), Z(z), W(w)
        {
            Vector4 s;
        }

        Vector4::Vector4(const Vector3& original, float W)
            : X(original.X), Y(original.Y), Z(original.Z), W(W)
        {
        }

        Vector4::Vector4(const Vector4& original)
            : X(original.X), Y(original.Y), Z(original.Z), W(original.W)
        {
        }

        Vector4 Vector4::operator + () const
        {
            return Vector4(+X, +Y, +Z, +W);
        }

        Vector4 Vector4::operator - () const
        {
            return Vector4(-X, -Y, -Z, -W);
        }

        Vector4& Vector4::operator = (const Vector4& right)
        {
            X = right.X;
            Y = right.Y;
            Z = right.Z;
            W = right.W;
            return *this;
        }

        Vector4& Vector4::operator += (const Vector4& right)
        {
            X += right.X;
            Y += right.Y;
            Z += right.Z;
            W += right.W;
            return *this;
        }

        Vector4& Vector4::operator -= (const Vector4& right)
        {
            X -= right.X;
            Y -= right.Y;
            Z -= right.Z;
            W -= right.W;
            return *this;
        }

        Vector4& Vector4::operator *= (float right)
        {
            X *= right;
            Y *= right;
            Z *= right;
            W *= right;
            return *this;
        }

        Vector4& Vector4::operator /= (float right)
        {
            X /= right;
            Y /= right;
            Z /= right;
            W /= right;
            return *this;
        }

        Vector4 Vector4::operator + (const Vector4& right) const
        {
            return Vector4(X + right.X, Y + right.Y, Z + right.Z, W + right.W);
        }

        Vector4 Vector4::operator - (const Vector4& right) const
        {
            return Vector4(X - right.X, Y - right.Y, Z - right.Z, W - right.W);
        }

        Vector4 Vector4::operator * (float right) const
        {
            return Vector4(X * right, Y * right, Z * right, W * right);
        }

        Vector4 Vector4::operator / (float right) const
        {
            return Vector4(X / right, Y / right, Z / right, W / right);
        }

        bool Vector4::operator == (const Vector4& right) const
        {
            return X == right.X && Y == right.Y && Z == right.Z && W == right.W;
        }

        bool Vector4::operator != (const Vector4& right) const
        {
            return !operator == (right);
        }

        Vector4 operator * (float left, const Vector4& right)
        {
            return Vector4(left * right.X, left * right.Y, left * right.Z, left * right.W);
        }
    }

#endif