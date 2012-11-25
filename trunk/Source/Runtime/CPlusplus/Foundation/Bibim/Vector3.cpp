#include <Bibim/PCH.h>
#include <Bibim/Vector3.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>

namespace Bibim
{
    float Vector3::Normalize()
    {
        // 크기가 1이면 Normalize를 수행하지 않습니다.
        if (Math::Equals(X * X + Y * Y + Z * Z, 1.0f))
            return 1.0f;

        const float length = GetLength();

        X /= length;
        Y /= length;
        Z /= length;

        return length;
    }

    void Vector3::Rotate(Vector3 axis, float rotation)
    {
        Rotate(axis, Math::Sin(rotation), Math::Cos(rotation));
    }

    void Vector3::Rotate(Vector3 axis, float sin, float cos)
    {
        const Vector3 v = Vector3(X, Y, Z);

        /*
+    D3DXVECTOR3 v;
+
+    D3DXVec3Normalize(&v,pv);
+    D3DXMatrixIdentity(pout);
+    pout->m[0][0] = (1.0f - cos(angle)) * v.x * v.x + cos(angle);
+    pout->m[1][0] = (1.0f - cos(angle)) * v.x * v.y - sin(angle) * v.z;
+    pout->m[2][0] = (1.0f - cos(angle)) * v.x * v.z + sin(angle) * v.y;
+    pout->m[0][1] = (1.0f - cos(angle)) * v.y * v.x + sin(angle) * v.z;
+    pout->m[1][1] = (1.0f - cos(angle)) * v.y * v.y + cos(angle);
+    pout->m[2][1] = (1.0f - cos(angle)) * v.y * v.z - sin(angle) * v.x;
+    pout->m[0][2] = (1.0f - cos(angle)) * v.z * v.x - sin(angle) * v.y;
+    pout->m[1][2] = (1.0f - cos(angle)) * v.z * v.y + sin(angle) * v.x;
+    pout->m[2][2] = (1.0f - cos(angle)) * v.z * v.z + cos(angle);
*/
        const float icos = (1.0f - cos);

        X = (v.X * ((icos * axis.X * axis.X) + (cos))) +
            (v.Y * ((icos * axis.X * axis.Y) - (sin * axis.Z))) +
            (v.Z * ((icos * axis.X * axis.Z) + (sin * axis.Y)));

        Y = (v.X * ((icos * axis.Y * axis.X) + (sin * axis.Z))) +
            (v.Y * ((icos * axis.Y * axis.Y) + (cos))) +
            (v.Z * ((icos * axis.Y * axis.Z) - (sin * axis.X)));

        Z = (v.X * ((icos * axis.Z * axis.X) - (sin * axis.Y))) +
            (v.Y * ((icos * axis.Z * axis.Y) + (sin * axis.X))) +
            (v.Z * ((icos * axis.Z * axis.Z) + (cos)));
    }

    float Vector3::GetLength() const
    {
        return Math::Sqrt((X * X) + (Y * Y) + (Z * Z));
    }

    float Vector3::GetLengthSquared() const
    {
        return (X * X) + (Y * Y) + (Z * Z);
    }

    float Vector3::GetDistance(Vector3 a, Vector3 b)
    {
        return Math::Sqrt(GetDistanceSquared(a, b));
    }

    float Vector3::GetDistanceSquared(Vector3 a, Vector3 b)
    {
        return (b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y) + (b.Z - a.Z) * (b.Y - a.Z);
    }

    const Vector3 Vector3::Zero  = Vector3(0.0f, 0.0f, 0.0f);
    const Vector3 Vector3::UnitX = Vector3(1.0f, 0.0f, 0.0f);
    const Vector3 Vector3::UnitY = Vector3(0.0f, 1.0f, 0.0f);
    const Vector3 Vector3::UnitZ = Vector3(0.0f, 0.0f, 1.0f);
    const Vector3 Vector3::One   = Vector3(1.0f, 1.0f, 1.0f);
    const Vector3 Vector3::Minimum = Vector3(Float::Min, Float::Min, Float::Min);
    const Vector3 Vector3::Maximum = Vector3(Float::Max, Float::Max, Float::Max);
}