#include <Bibim/PCH.h>
#include <Bibim/Matrix4.h>
#include <Bibim/Math.h>
#include <d3dx9math.h>

namespace Bibim
{
    Matrix4::Matrix4()
    {
    }

    Matrix4::Matrix4(float m00, float m01, float m02, float m03,
                     float m10, float m11, float m12, float m13,
                     float m20, float m21, float m22, float m23,
                     float m30, float m31, float m32, float m33)
        : M00(m00), M01(m01), M02(m02), M03(m03),
          M10(m10), M11(m11), M12(m12), M13(m13),
          M20(m20), M21(m21), M22(m22), M23(m23),
          M30(m30), M31(m31), M32(m32), M33(m33)
    {
    }

    Matrix4::Matrix4(const float* values)
        : M00(values[0]),  M01(values[1]),  M02(values[2]),  M03(values[3]),
          M10(values[4]),  M11(values[5]),  M12(values[6]),  M13(values[7]),
          M20(values[8]),  M21(values[9]),  M22(values[10]), M23(values[11]),
          M30(values[12]), M31(values[13]), M32(values[14]), M33(values[15])
    {
    }

    Matrix4::Matrix4(const Matrix4& original)
        : M00(original.M00), M01(original.M01), M02(original.M02), M03(original.M03),
          M10(original.M10), M11(original.M11), M12(original.M12), M13(original.M13),
          M20(original.M20), M21(original.M21), M22(original.M22), M23(original.M23),
          M30(original.M30), M31(original.M31), M32(original.M32), M33(original.M33)
    {
    }

    Matrix4 Matrix4::operator + () const
    {
        return Matrix4(+M00, +M01, +M02, +M03,
                       +M10, +M11, +M12, +M13,
                       +M20, +M21, +M22, +M23,
                       +M30, +M31, +M32, +M33);
    }

    Matrix4 Matrix4::operator - () const
    {
        return Matrix4(-M00, -M01, -M02, -M03,
                       -M10, -M11, -M12, -M13,
                       -M20, -M21, -M22, -M23,
                       -M30, -M31, -M32, -M33);
    }

    Matrix4& Matrix4::operator = (const Matrix4& right)
    {
        M00 = right.M00; M01 = right.M01; M02 = right.M02; M03 = right.M03;
        M10 = right.M10; M11 = right.M11; M12 = right.M12; M13 = right.M13;
        M20 = right.M20; M21 = right.M21; M22 = right.M22; M23 = right.M23;
        M30 = right.M30; M31 = right.M31; M32 = right.M32; M33 = right.M33;
        return *this;
    }

    Matrix4& Matrix4::operator += (const Matrix4& right)
    {
        M00 += right.M00; M01 += right.M01; M02 += right.M02; M03 += right.M03;
        M10 += right.M10; M11 += right.M11; M12 += right.M12; M13 += right.M13;
        M20 += right.M20; M21 += right.M21; M22 += right.M22; M23 += right.M23;
        M30 += right.M30; M31 += right.M31; M32 += right.M32; M33 += right.M33;
        return *this;
    }

    Matrix4& Matrix4::operator -= (const Matrix4& right)
    {
        M00 -= right.M00; M01 -= right.M01; M02 -= right.M02; M03 -= right.M03;
        M10 -= right.M10; M11 -= right.M11; M12 -= right.M12; M13 -= right.M13;
        M20 -= right.M20; M21 -= right.M21; M22 -= right.M22; M23 -= right.M23;
        M30 -= right.M30; M31 -= right.M31; M32 -= right.M32; M33 -= right.M33;
        return *this;
    }

    Matrix4& Matrix4::operator *= (const Matrix4& right)
    {
        (*this) = (*this) * right;
        return *this;
    }

    Matrix4& Matrix4::operator *= (float right)
    {
        M00 *= right; M01 *= right; M02 *= right; M03 *= right;
        M10 *= right; M11 *= right; M12 *= right; M13 *= right;
        M20 *= right; M21 *= right; M22 *= right; M23 *= right;
        M30 *= right; M31 *= right; M32 *= right; M33 *= right;
        return *this;
    }

    Matrix4 Matrix4::operator + (const Matrix4& right) const
    {
        return Matrix4(M00 + right.M00, M01 + right.M01, M02 + right.M02, M03 + right.M03,
                       M10 + right.M10, M11 + right.M11, M12 + right.M12, M13 + right.M13,
                       M20 + right.M20, M21 + right.M21, M22 + right.M22, M23 + right.M23,
                       M30 + right.M30, M31 + right.M31, M32 + right.M32, M33 + right.M33);
    }

    Matrix4 Matrix4::operator - (const Matrix4& right) const
    {
        return Matrix4(M00 - right.M00, M01 - right.M01, M02 - right.M02, M03 - right.M03,
                       M10 - right.M10, M11 - right.M11, M12 - right.M12, M13 - right.M13,
                       M20 - right.M20, M21 - right.M21, M22 - right.M22, M23 - right.M23,
                       M30 - right.M30, M31 - right.M31, M32 - right.M32, M33 - right.M33);
    }

    Matrix4 Matrix4::operator * (const Matrix4& right) const
    {
        return Matrix4(M00 * right.M00 + M01 * right.M10 + M02 * right.M20 + M03 * right.M30,
                       M00 * right.M01 + M01 * right.M11 + M02 * right.M21 + M03 * right.M31,
                       M00 * right.M02 + M01 * right.M12 + M02 * right.M22 + M03 * right.M32,
                       M00 * right.M03 + M01 * right.M13 + M02 * right.M23 + M03 * right.M33,

                       M10 * right.M00 + M11 * right.M10 + M12 * right.M20 + M13 * right.M30,
                       M10 * right.M01 + M11 * right.M11 + M12 * right.M21 + M13 * right.M31,
                       M10 * right.M02 + M11 * right.M12 + M12 * right.M22 + M13 * right.M32,
                       M10 * right.M03 + M11 * right.M13 + M12 * right.M23 + M13 * right.M33,

                       M20 * right.M00 + M21 * right.M10 + M22 * right.M20 + M23 * right.M30,
                       M20 * right.M01 + M21 * right.M11 + M22 * right.M21 + M23 * right.M31,
                       M20 * right.M02 + M21 * right.M12 + M22 * right.M22 + M23 * right.M32,
                       M20 * right.M03 + M21 * right.M13 + M22 * right.M23 + M23 * right.M33,

                       M30 * right.M00 + M31 * right.M10 + M32 * right.M20 + M33 * right.M30,
                       M30 * right.M01 + M31 * right.M11 + M32 * right.M21 + M33 * right.M31,
                       M30 * right.M02 + M31 * right.M12 + M32 * right.M22 + M33 * right.M32,
                       M30 * right.M03 + M31 * right.M13 + M32 * right.M23 + M33 * right.M33);
    }

    Matrix4 Matrix4::operator * (float right) const
    {
        return Matrix4(M00 * right, M01 * right, M02 * right, M03 * right,
                       M10 * right, M11 * right, M12 * right, M13 * right,
                       M20 * right, M21 * right, M22 * right, M23 * right,
                       M30 * right, M31 * right, M32 * right, M33 * right);
    }

    bool Matrix4::operator == (const Matrix4& right) const
    {
        return (M00 == right.M00 && M01 == right.M01 && M02 == right.M02 && M03 == right.M03 &&
                M10 == right.M10 && M11 == right.M11 && M12 == right.M12 && M13 == right.M13 &&
                M20 == right.M20 && M21 == right.M21 && M22 == right.M22 && M23 == right.M23 &&
                M30 == right.M30 && M31 == right.M31 && M32 == right.M32 && M33 == right.M33);
    }

    bool Matrix4::operator != (const Matrix4& right) const
    {
        return !operator == (right);
    }

    Matrix4 Matrix4::Translation(Vector3 value)
    {
        return Matrix4(1.0f,    0.0f,    0.0f,    0.0f,
                       0.0f,    1.0f,    0.0f,    0.0f,
                       0.0f,    0.0f,    1.0f,    0.0f,
                       value.X, value.Y, value.Z, 1.0f);
    }

    Matrix4 Matrix4::RotationX(float value)
    {
        const float sin = Math::Sin(value);
        const float cos = Math::Cos(value);
        return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, +cos, -sin, 0.0f,
                       0.0f, +sin, +cos, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::RotationY(float value)
    {
        const float sin = Math::Sin(value);
        const float cos = Math::Cos(value);
        return Matrix4(+cos, 0.0f, +sin, 0.0f,
                       0.0f, 1.0f, 0.0f, 0.0f,
                       -sin, 0.0f, +cos, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::RotationZ(float value)
    {
        const float sin = Math::Sin(value);
        const float cos = Math::Cos(value);
        return Matrix4(+cos, -sin, 0.0f, 0.0f,
                       +sin, +cos, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    }

    Matrix4 Matrix4::Scaling(float value)
    {
        return Matrix4(value, 0.0f,  0.0f,  0.0f,
                       0.0f,  value, 0.0f,  0.0f,
                       0.0f,  0.0f,  value, 0.0f,
                       0.0f,  0.0f,  0.0f,  1.0f);
    }

    Matrix4 Matrix4::Scaling(Vector3 value)
    {
        return Matrix4(value.X, 0.0f,    0.0f,    0.0f,
                       0.0f,    value.Y, 0.0f,    0.0f,
                       0.0f,    0.0f,    value.Z, 0.0f,
                       0.0f,    0.0f,    0.0f,    1.0f);
    }

    Matrix4 Matrix4::Inversion(const Matrix4& value)
    {
        float const * const m = &value.M00;

        float inv[16];
        inv[0] = m[5]  * m[10] * m[15] - 
                 m[5]  * m[11] * m[14] - 
                 m[9]  * m[6]  * m[15] + 
                 m[9]  * m[7]  * m[14] +
                 m[13] * m[6]  * m[11] - 
                 m[13] * m[7]  * m[10];

        inv[4] = -m[4]  * m[10] * m[15] + 
                  m[4]  * m[11] * m[14] + 
                  m[8]  * m[6]  * m[15] - 
                  m[8]  * m[7]  * m[14] - 
                  m[12] * m[6]  * m[11] + 
                  m[12] * m[7]  * m[10];

        inv[8] = m[4]  * m[9]  * m[15] - 
                 m[4]  * m[11] * m[13] - 
                 m[8]  * m[5]  * m[15] + 
                 m[8]  * m[7]  * m[13] + 
                 m[12] * m[5]  * m[11] - 
                 m[12] * m[7]  * m[9];

        inv[12] = -m[4]  * m[9]  * m[14] + 
                   m[4]  * m[10] * m[13] +
                   m[8]  * m[5]  * m[14] - 
                   m[8]  * m[6]  * m[13] - 
                   m[12] * m[5]  * m[10] + 
                   m[12] * m[6]  * m[9];

        inv[1] = -m[1]  * m[10] * m[15] + 
                  m[1]  * m[11] * m[14] + 
                  m[9]  * m[2]  * m[15] - 
                  m[9]  * m[3]  * m[14] - 
                  m[13] * m[2]  * m[11] + 
                  m[13] * m[3]  * m[10];

        inv[5] = m[0]  * m[10] * m[15] - 
                 m[0]  * m[11] * m[14] - 
                 m[8]  * m[2]  * m[15] + 
                 m[8]  * m[3]  * m[14] + 
                 m[12] * m[2]  * m[11] - 
                 m[12] * m[3]  * m[10];

        inv[9] = -m[0]  * m[9]  * m[15] + 
                  m[0]  * m[11] * m[13] + 
                  m[8]  * m[1]  * m[15] - 
                  m[8]  * m[3]  * m[13] - 
                  m[12] * m[1]  * m[11] + 
                  m[12] * m[3]  * m[9];

        inv[13] = m[0]  * m[9]  * m[14] - 
                  m[0]  * m[10] * m[13] - 
                  m[8]  * m[1]  * m[14] + 
                  m[8]  * m[2]  * m[13] + 
                  m[12] * m[1]  * m[10] - 
                  m[12] * m[2]  * m[9];

        inv[2] = m[1]  * m[6] * m[15] - 
                 m[1]  * m[7] * m[14] - 
                 m[5]  * m[2] * m[15] + 
                 m[5]  * m[3] * m[14] + 
                 m[13] * m[2] * m[7] - 
                 m[13] * m[3] * m[6];

        inv[6] = -m[0]  * m[6] * m[15] + 
                  m[0]  * m[7] * m[14] + 
                  m[4]  * m[2] * m[15] - 
                  m[4]  * m[3] * m[14] - 
                  m[12] * m[2] * m[7] + 
                  m[12] * m[3] * m[6];

        inv[10] = m[0]  * m[5] * m[15] - 
                  m[0]  * m[7] * m[13] - 
                  m[4]  * m[1] * m[15] + 
                  m[4]  * m[3] * m[13] + 
                  m[12] * m[1] * m[7] - 
                  m[12] * m[3] * m[5];

        inv[14] = -m[0]  * m[5] * m[14] + 
                   m[0]  * m[6] * m[13] + 
                   m[4]  * m[1] * m[14] - 
                   m[4]  * m[2] * m[13] - 
                   m[12] * m[1] * m[6] + 
                   m[12] * m[2] * m[5];

        inv[3] = -m[1] * m[6] * m[11] + 
                  m[1] * m[7] * m[10] + 
                  m[5] * m[2] * m[11] - 
                  m[5] * m[3] * m[10] - 
                  m[9] * m[2] * m[7] + 
                  m[9] * m[3] * m[6];

        inv[7] = m[0] * m[6] * m[11] - 
                 m[0] * m[7] * m[10] - 
                 m[4] * m[2] * m[11] + 
                 m[4] * m[3] * m[10] + 
                 m[8] * m[2] * m[7] - 
                 m[8] * m[3] * m[6];

        inv[11] = -m[0] * m[5] * m[11] + 
                   m[0] * m[7] * m[9] + 
                   m[4] * m[1] * m[11] - 
                   m[4] * m[3] * m[9] - 
                   m[8] * m[1] * m[7] + 
                   m[8] * m[3] * m[5];

        inv[15] = m[0] * m[5] * m[10] - 
                  m[0] * m[6] * m[9] - 
                  m[4] * m[1] * m[10] + 
                  m[4] * m[2] * m[9] + 
                  m[8] * m[1] * m[6] - 
                  m[8] * m[2] * m[5];

        float determinant = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
        if (determinant == 0.0f)
            return Matrix4::Zero;

        determinant = 1.0f / determinant;

        for (int i = 0; i < 16; i++)
            inv[i] = inv[i] * determinant;

        return Matrix4(inv);
    }

    Matrix4 Matrix4::Transpose(const Matrix4& value)
    {
        return Matrix4(value.M00, value.M10, value.M20, value.M30,
                       value.M01, value.M11, value.M21, value.M31,
                       value.M02, value.M12, value.M22, value.M32,
                       value.M03, value.M13, value.M23, value.M33);
    }

    Matrix4 operator * (float left, const Matrix4& right)
    {
        return right * left;
    }
    
    const Matrix4 Matrix4::Zero(0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f);
    const Matrix4 Matrix4::Identity(1.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f);
}