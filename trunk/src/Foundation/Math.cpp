#include <Bibim/Config.h>
#include <Bibim/Math.h>
#include <Bibim/Assert.h>
#include <cmath>
#include <cstdlib>

namespace Bibim
{
    const float Math::E = 2.71828f;
    const float Math::Log10E = 0.434294f;
    const float Math::Log2E = 1.4427f;
    const float Math::Pi = 3.14159f;
    const float Math::PiOver2 = 1.5708f;
    const float Math::PiOver4 = 0.785398f;
    const float Math::TwoPi = 6.28319f;
    const float Math::InvSqrt2 = 0.707106781186f;

    float Math::Sqrt(float value)
    {
        return std::sqrt(value);
    }

    float Math::Pow(float x, float y)
    {
        return std::pow(x, y);
    }

    float Math::Sin(float radian)
    {
        return std::sin(radian);
    }

    float Math::Cos(float radian)
    {
        return std::cos(radian);
    }

    float Math::Tan(float radian)
    {
        return std::tan(radian);    
    }

    float Math::Asin(float radian)
    {
        return std::asin(radian);
    }

    float Math::Acos(float radian)
    {
        return std::acos(radian);
    }

    float Math::Atan2(float y, float x)
    {
        return std::atan2(y, x);
    }

    float Math::Floor(float value)
    {
        return std::floor(value);
    }

    float Math::Exp(float value)
    {
        return std::exp(value);
    }

    float Math::Mod(float a, float b)
    {
        return std::fmod(a, b);
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

    Vector2 Math::CatmullRom(Vector2 a, Vector2 b, Vector2 c, Vector2 d, float t)
    {
        return 0.5f * 
                (
                    (2.0f * b) + 
                    ((-a + c) * (t)) +
                    (((2.0f * a) - (5.0f * b) + (4.0f * c) - d) * (t * t)) + 
                    ((-a + (3.0f * b) - (3.0f * c) + d) * (t * t * t))
                );
    }
}