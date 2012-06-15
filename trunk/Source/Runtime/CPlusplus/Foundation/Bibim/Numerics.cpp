#include <Bibim/PCH.h>
#include <Bibim/Numerics.h>
#include <float.h>
#include <limits.h>
#include <stdlib.h>

namespace Bibim
{
    const byte Byte::Min = 0;
    const byte Byte::Max = UCHAR_MAX;

    byte Byte::Parse(const char* s, int /*length*/)
    {
        if (s == nullptr)
            return 0;

        const int result = atoi(s);
        if (result < Min)
            return Min;
        if (result > Max)
            return Max;

        return static_cast<byte>(result);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const short ShortInt::Min = SHRT_MIN;
    const short ShortInt::Max = SHRT_MAX;

    short ShortInt::Parse(const char* s, int /*length*/)
    {
        if (s == nullptr)
            return 0;

        const int result = atoi(s);
        if (result < Min)
            return Min;
        if (result > Max)
            return Max;

        return static_cast<short>(result);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const int Int::Min = INT_MIN;
    const int Int::Max = INT_MAX;

    int Int::Parse(const char* s, int /*length*/)
    {
        if (s == nullptr)
            return 0;

        return static_cast<int>(atoi(s));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const longint LongInt::Min = LLONG_MIN;
    const longint LongInt::Max = LLONG_MAX;

    longint LongInt::Parse(const char* s, int /*length*/)
    {
        if (s == nullptr)
            return 0;

        return static_cast<longint>(_atoi64(s));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const float Float::Min = FLT_MIN;
    const float Float::Max = FLT_MAX;

    float Float::Parse(const char* s, int /*length*/)
    {
        if (s == nullptr)
            return 0.0f;

        return static_cast<float>(atof(s));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const double Double::Min = DBL_MIN;
    const double Double::Max = DBL_MAX;

    double Double::Parse(const char* s, int /*length*/)
    {
        if (s == nullptr)
            return 0.0;

        return static_cast<double>(atof(s));
    }
}