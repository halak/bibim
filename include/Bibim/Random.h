#pragma once
#ifndef __BIBIM_RANDOM_H__
#define __BIBIM_RANDOM_H__

#include <Bibim/Foundation.h>

namespace Bibim
{
    /// `WELL512a` 난수 생성 알고리즘을 클래스로 래핑하였습니다.
    /// http://www.iro.umontreal.ca/~panneton/WELLRNG.html
    class Random
    {
        public:
            Random();
            Random(uint seed);
            Random(const Random& original);

            //uint Generate();

            Random& operator = (const Random& right);

        private:
            static const int W = 32;
            static const int R = 16;
            static const int P = 0;
            static const int M1 = 13;
            static const int M2 = 9;
            static const int M3 = 5;
            static const double FACT;

            uint index;
            uint states[R];
    };

}

/* ***************************************************************************** */
/* Copyright:      Francois Panneton and Pierre L'Ecuyer, University of Montreal */
/*                 Makoto Matsumoto, Hiroshima University                        */
/* Notice:         This code can be used freely for personal, academic,          */
/*                 or non-commercial purposes. For commercial purposes,          */
/*                 please contact P. L'Ecuyer at: lecuyer@iro.UMontreal.ca       */
/* ***************************************************************************** */

#endif