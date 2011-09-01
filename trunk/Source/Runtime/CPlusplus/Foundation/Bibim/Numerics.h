#pragma once
#ifndef __BIBIM_NUMERICS_H__
#define __BIBIM_NUMERICS_H__

#   include <Bibim/Foundation.h>

    namespace Bibim
    {
        struct Char
        {
            static const char Min;
            static const char Max;
        };

        struct UChar
        {
            static const uchar Min;
            static const uchar Max;
        };

        struct  Short
        {
            static const short Min;
            static const short Max;
        };

        struct UShort
        {
            static const ushort Min;
            static const ushort Max;
        };
        

        struct Int
        {
            static const int Min;
            static const int Max;
        };

        struct UInt
        {
            static const uint Min;
            static const uint Max;
        };

        struct Long
        {
            static const long Min;
            static const long Max;
        };

        struct ULong
        {
            static const ulong Min;
            static const ulong Max;
        };

        struct Float
        {
            static const float Min;
            static const float Max;
            static const float NaN;
        };

        struct Double
        {
            static const double Min;
            static const double Max;
            static const double NaN;
        };

        struct Int64
        {
            static const int64 Min;
            static const int64 Max;
        };

        struct UInt64
        {
            static const uint64 Min;
            static const uint64 Max;
        };

        typedef Char   Int8;
        typedef UChar  Byte;
        typedef UChar  UInt8;
        typedef Short  Int16;
        typedef UShort UInt16;
        typedef UShort Word;
        typedef Int    Int32;
        typedef UInt   UInt32;
        typedef ULong  DWord;
        typedef Float  Real32;
        typedef Double Real64;
        typedef UInt64 QWord;
    }

#endif