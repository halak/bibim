#include <Bibim/Config.h>
#include <Bibim/Random.h>

namespace Bibim
{
    Random::Random()
        : seed(0)
    {
        Generate();
    }

    Random::Random(uint seed)
        : seed(seed)
    {
        Generate();
    }

    Random::Random(const Random& original)
        : seed(original.seed)
    {
    }

    unsigned int Random::Generate()
    {
        // TODO: 제대로 된 알고리즘으로 수정해야합니다.

        seed *= seed;
        seed ^= 0x2A3E268F;
        seed >>= seed & 0xf;
        return seed;
    }

    Random& Random::operator = (const Random& right)
    {
        seed = right.seed;
        return *this;
    }
}