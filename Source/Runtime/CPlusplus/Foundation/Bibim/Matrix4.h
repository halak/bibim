#pragma once
#ifndef __BIBIM_MATRIX4_H__
#define __BIBIM_MATRIX4_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Vector3.h>

    namespace Bibim
    {
        struct Matrix4
        {
            float M00, M01, M02, M03;
            float M10, M11, M12, M13;
            float M20, M21, M22, M23;
            float M30, M31, M32, M33;

            Matrix4();
            Matrix4(float m00, float m01, float m02, float m03,
                    float m10, float m11, float m12, float m13,
                    float m20, float m21, float m22, float m23,
                    float m30, float m31, float m32, float m33);
            Matrix4(const float* values);
            Matrix4(const Matrix4& original);

            Matrix4 operator + () const;
            Matrix4 operator - () const;

            Matrix4& operator = (const Matrix4& right);
            Matrix4& operator += (const Matrix4& right);
            Matrix4& operator -= (const Matrix4& right);
            Matrix4& operator *= (const Matrix4& right);
            Matrix4& operator *= (float right);
            Matrix4  operator + (const Matrix4& right) const;
            Matrix4  operator - (const Matrix4& right) const;
            Matrix4  operator * (const Matrix4& right) const;
            Matrix4  operator * (float right) const;
            bool operator == (const Matrix4& right) const;
            bool operator != (const Matrix4& right) const;

            inline operator float* ();
            inline operator const float* () const;

            static Matrix4 Translation(Vector3 value);
            static Matrix4 RotationX(float value);
            static Matrix4 RotationY(float value);
            static Matrix4 RotationZ(float value);
            static Matrix4 Scaling(float value);
            static Matrix4 Scaling(Vector3 value);
            static Matrix4 Inversion(const Matrix4& value);
            static Matrix4 Transpose(const Matrix4& value);

            friend Matrix4 operator * (float left, const Matrix4& right);

            static const Matrix4 Zero;
            static const Matrix4 Identity;
        };
    }

#   include <Bibim/Matrix4.inl>

#endif