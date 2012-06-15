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

    float Vector3::GetLength() const
    {
        return Math::Sqrt((X * X) + (Y * Y) + (Z * Z));
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