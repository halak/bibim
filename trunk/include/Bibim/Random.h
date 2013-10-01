#pragma once
#ifndef __BIBIM_RANDOM_H__
#define __BIBIM_RANDOM_H__

#include <Bibim/Foundation.h>

namespace Bibim
{
    class Random
    {
        public:
            Random();
            Random(uint seed);
            Random(const Random& original);

            uint Generate();

            Random& operator = (const Random& right);
            inline bool operator == (const Random& right) const;
            inline bool operator != (const Random& right) const;

        private:
            uint seed;
    };

    bool Random::operator == (const Random& right) const
    {
        return seed == right.seed;
    }

    bool Random::operator != (const Random& right) const
    {
        return !operator == (right);
    }
}

#endif