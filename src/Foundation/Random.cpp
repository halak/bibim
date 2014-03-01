#include <Bibim/Config.h>
#include <Bibim/Random.h>

namespace Bibim
{
    Random Rand::Global;

    const double Random::FACT = 2.32830643653869628906e-10;

    #define MAT0POS(t,v) (v^(v>>t))
    #define MAT0NEG(t,v) (v^(v<<(-(t))))
    #define MAT3NEG(t,v) (v<<(-(t)))
    #define MAT4NEG(t,b,v) (v ^ ((v<<(-(t))) & b))

    #define V0            states[index]
    #define VM1           states[(index+M1) & 0x0000000fU]
    #define VM2           states[(index+M2) & 0x0000000fU]
    #define VM3           states[(index+M3) & 0x0000000fU]
    #define VRm1          states[(index+15) & 0x0000000fU]
    #define VRm2          states[(index+14) & 0x0000000fU]
    #define newV0         states[(index+15) & 0x0000000fU]
    #define newV1         states[index]
    #define newVRm1       states[(index+14) & 0x0000000fU]

    Random::Random()
        : index(0)
    {
        for (int i = 0; i < sizeof(states) / sizeof(states[0]); i++)
            states[i] = i;
    }

    Random::Random(uint seed)
        : index(0)
    {
        for (int i = 0; i < sizeof(states) / sizeof(states[0]); i++)
            states[i] = seed + i;
    }

    Random::Random(const Random& original)
        : index(original.index)
    {
        for (int i = 0; i < sizeof(states) / sizeof(states[0]); i++)
            states[i] = original.states[i];
    }

    double Random::Next()
    {
        const uint z0 = VRm1;
        const uint z1 = MAT0NEG(-16,V0) ^ MAT0NEG (-15, VM1);
        const uint z2 = MAT0POS(11, VM2);
        newV1 = z1 ^ z2; 
        newV0 = MAT0NEG(-2, z0) ^ MAT0NEG(-18, z1) ^ MAT3NEG(-28, z2) ^ MAT4NEG(-5, 0xda442d24U, newV1);

        index = (index + 15) & 0x0000000fU;
        return ((double) states[index]) * FACT;
    }

    bool Random::TrueOrFalse()
    {
        return Next() < 0.5;
    }

    int Random::Range(int a, int b)
    {
        return a + static_cast<int>(static_cast<double>(b - a) * Next());
    }

    float Random::Range(float a, float b)
    {
        return a + static_cast<float>(static_cast<double>(b - a) * Next());
    }

    double Random::Range(double a, double b)
    {
        return a + ((b - a) * Next());
    }

    Vector2 Random::Range(Vector2 a, Vector2 b)
    {
        return Vector2(Range(a.X, b.X), Range(a.Y, b.Y));
    }

    Vector3 Random::Range(Vector3 a, Vector3 b)
    {
        return Vector3(Range(a.X, b.X), Range(a.Y, b.Y), Range(a.Z, b.Z));
    }

    Vector4 Random::Range(Vector4 a, Vector4 b)
    {
        return Vector4(Range(a.X, b.X), Range(a.Y, b.Y), Range(a.Z, b.Z), Range(a.W, b.W));
    }

    Color Random::Range(Color a, Color b)
    {
        return Color(Range(a.R, b.R), Range(a.G, b.G), Range(a.B, b.B), Range(a.A, b.A));
    }

    Random& Random::operator = (const Random& right)
    {
        index = right.index;
        for (int i = 0; i < sizeof(states) / sizeof(states[0]); i++)
            states[i] = right.states[i];
        return *this;
    }

    #undef MAT0POS
    #undef MAT0NEG
    #undef MAT3NEG
    #undef MAT4NEG

    #undef V0
    #undef VM1
    #undef VM2
    #undef VM3
    #undef VRm1
    #undef VRm2
    #undef newV0
    #undef newV1
    #undef newVRm1
}