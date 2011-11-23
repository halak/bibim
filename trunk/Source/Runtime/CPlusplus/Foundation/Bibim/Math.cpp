#include <Bibim/PCH.h>
#include <Bibim/Math.h>
#include <Bibim/Assert.h>
#include <cmath>

namespace Bibim
{
    const float Math::E = 2.71828f;
    const float Math::Log10E = 0.434294f;
    const float Math::Log2E = 1.4427f;
    const float Math::Pi = 3.14159f;
    const float Math::PiOver2 = 1.5708f;
    const float Math::PiOver4 = 0.785398f;
    const float Math::TwoPi = 6.28319f;

    float Math::Sqrt(float value)
    {
        return std::sqrtf(value);
    }

    float Math::Pow(float x, float y)
    {
        return std::powf(x, y);
    }

    float Math::Sin(float radian)
    {
        return std::sinf(radian);
    }

    float Math::Cos(float radian)
    {
        return std::cosf(radian);
    }

    float Math::Tan(float radian)
    {
        return std::tanf(radian);    
    }

    float Math::Asin(float radian)
    {
        return std::asinf(radian);
    }

    float Math::Acos(float radian)
    {
        return std::acosf(radian);
    }

    float Math::Atan2(float y, float x)
    {
        return std::atan2(y, x);
    }

    float Math::Exp(float value)
    {
        return std::expf(value);
    }

    float Math::Mod(float a, float b)
    {
        return std::fmodf(a, b);
    }

    double Mod(double a, double b)
    {
        return std::fmod(a, b);
    }

    int Math::GetNearestPowerOfTwo(int value)
    {
        if (value > 0)
        {
            value--;
            value |= (value >> 1);
            value |= (value >> 2);
            value |= (value >> 4);
            value |= (value >> 8);
            value |= (value >> 16);
            value++;
            return value;
        }
        else
            return 0;
    }

    bool Math::Equals(float a, float b)
    {
        return std::abs(a - b) < 0.00001f;
    }

    bool Math::Equals(Vector2 a, Vector2 b)
    {
        return Equals(a.X, b.X) && Equals(a.Y, b.Y);
    }

    bool Math::Equals(Vector3 a, Vector3 b)
    {
        return Equals(a.X, b.X) && Equals(a.Y, b.Y) && Equals(a.Z, b.Z);
    }

    Vector2 Math::GetClosestPoint(Vector2 origin, Vector2 direction, float length, Vector2 point)
    {
        return origin + (direction * Clamp(direction.Dot(point - origin), 0.0f, length));
    }

    bool Math::IsClockwise(Vector2 a, Vector2 b, Vector2 c)
    {
        // Right-handed
        // http://www.dsource.org/projects/blaze/changeset/63
        return ((b.X - a.X) * (c.Y - a.Y) - (c.X - a.X) * (b.Y - a.Y)) > 0.0f;
    }

    bool Math::IsClockwise(const Vector2* points, int numberOfPoints)
    {
        const int last = numberOfPoints - 1;
        float crossProductSum = (points[last].X * points[0].Y) - (points[0].X * points[last].Y);
        for (int i = 0; i < last; i++)
        {
            crossProductSum += (points[i].X * points[i + 1].Y) - (points[i + 1].X * points[i].Y);
        }

        return crossProductSum > 0.0f;
    }

    int Math::Random(int a, int b)
    {
        return a + (b - a) / 2;
        //std::tr1::uniform_int<int> u(Math::Min(a, b), Math::Max(a, b));
        //return u(globalRandomEngine);
    }

    float Math::Random(float a, float b)
    {
        return a + (b - a) / 2.0f;
        //std::tr1::uniform_real<float> u(Math::Min(a, b), Math::Max(a, b));
        //return u(globalRandomEngine);
    }

    Vector2 Math::Random(Vector2 a, Vector2 b)
    {
        return Vector2(Random(a.X, b.X), Random(a.Y, b.Y));
    }

    Vector3 Math::Random(Vector3 a, Vector3 b)
    {
        return Vector3(Random(a.X, b.X), Random(a.Y, b.Y), Random(a.Z, b.Z));
    }

    Vector4 Math::Random(Vector4 a, Vector4 b)
    {
        return Vector4(Random(a.X, b.X), Random(a.Y, b.Y), Random(a.Z, b.Z), Random(a.W, b.W));
    }

    Color Math::Random(Color a, Color b)
    {
        return Color(Random(a.R, b.R), Random(a.G, b.G), Random(a.B, b.B), Random(a.A, b.A));
    }
}