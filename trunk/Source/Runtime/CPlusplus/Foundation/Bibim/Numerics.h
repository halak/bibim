#pragma once
#ifndef __BIBIM_NUMERICS_H__
#define __BIBIM_NUMERICS_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/String.h>

    namespace Bibim
    {
        struct Byte
        {
            static const byte Min;
            static const byte Max;
        };

        struct  ShortInt
        {
            static const short Min;
            static const short Max;
        };

        struct Int
        {
            static const int Min;
            static const int Max;

            static int Parse(const String& s);
        };

        struct LongInt
        {
            static const longint Min;
            static const longint Max;
        };

        struct Float
        {
            static const float Min;
            static const float Max;
        };

        struct Double
        {
            static const double Min;
            static const double Max;
        };
    }

#endif