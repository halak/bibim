#include <Bibim/Config.h>
#include <Bibim/Numerics.h>
#include <float.h>
#include <limits.h>
#include <cstdlib>

// TODO: 코드 정리 좀 해야합니다.

namespace Bibim
{
    bool Bool::Parse(const char* s, int length)
    {
        if (s == nullptr)
            return false;

        if (length == 1)
        {
            return s[0] == 'Y' ||
                   s[0] == 'y' ||
                   s[0] == 'T' ||
                   s[0] == 't';
        }
        else if (length == 3)
        {
            return (s[0] == 'Y' || s[0] == 'y') &&
                   (s[1] == 'E' || s[1] == 'e') &&
                   (s[2] == 'S' || s[2] == 's');
        }
        else if (length == 4)
        {
            return (s[0] == 'T' || s[0] == 't') &&
                   (s[1] == 'R' || s[1] == 'r') &&
                   (s[2] == 'U' || s[2] == 'u') &&
                   (s[3] == 'E' || s[3] == 'e');
        }
        else
            return false;
    }

    const String& Bool::ToString(bool value)
    {
        static const String YES = "YES";
        static const String NO = "NO";
        return value ? YES : NO;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const byte Byte::Min = 0;
    const byte Byte::Max = UCHAR_MAX;

    byte Byte::Parse(const char* s, int /*length*/)
    {
        if (s == nullptr)
            return 0;

        const int result = std::atoi(s);
        if (result < Min)
            return Min;
        if (result > Max)
            return Max;

        return static_cast<byte>(result);
    }

    String Byte::ToString(byte value)
    {
        return Int::ToString(static_cast<int>(value));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const short ShortInt::Min = SHRT_MIN;
    const short ShortInt::Max = SHRT_MAX;

    short ShortInt::Parse(const char* s, int /*length*/)
    {
        if (s == nullptr)
            return 0;

        const int result = std::atoi(s);
        if (result < Min)
            return Min;
        if (result > Max)
            return Max;

        return static_cast<short>(result);
    }

    String ShortInt::ToString(short value)
    {
        return Int::ToString(static_cast<int>(value));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const int Int::Min = INT_MIN;
    const int Int::Max = INT_MAX;

    int Int::Parse(const char* s, int /*length*/)
    {
        if (s)
            return static_cast<int>(std::atoi(s));
        else
            return 0;
    }

    String Int::ToString(int value)
    {
        static const int BUFFER_LENGTH = 16;

        const bool isNegative = (value < 0);
        if (isNegative)
            value = -value;

        char s[BUFFER_LENGTH];
        s[BUFFER_LENGTH - 1] = '\0';

        int index = BUFFER_LENGTH - 2;
        do
        {
            s[index--] = "0123456789"[value % 10];
            value /= 10;
        } while (value > 0);

        if (isNegative)
            s[index] = '-';
        else
            index++;

        return String(&s[index], 0, BUFFER_LENGTH - 1 - index);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const longint LongInt::Min = LLONG_MIN;
    const longint LongInt::Max = LLONG_MAX;

    longint LongInt::Parse(const char* s, int /*length*/)
    {
        if (s)
        {
#           if (defined(BIBIM_PLATFORM_WINDOWS))
                return static_cast<longint>(_atoi64(s));
#           else
                return static_cast<longint>(atoll(s));
#           endif
        }
        else
            return 0;
    }

    String LongInt::ToString(longint value)
    {
        static const int BUFFER_LENGTH = 32;

        const bool isNegative = (value < 0);
        if (isNegative)
            value = -value;

        char s[BUFFER_LENGTH];
        s[BUFFER_LENGTH - 1] = '\0';

        int index = BUFFER_LENGTH - 2;
        do
        {
            s[index--] = "0123456789"[value % 10];
            value /= 10;
        } while (value > 0);

        if (isNegative)
            s[index] = '-';
        else
            index++;

        return String(&s[index], 0, BUFFER_LENGTH - 1 - index);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const float Float::Min = FLT_MIN;
    const float Float::Max = FLT_MAX;

    float Float::Parse(const char* s, int /*length*/)
    {
        if (s)
            return static_cast<float>(std::atof(s));
        else
            return 0.0f;
    }

    String Float::ToString(float value)
    {
        return String::CFormat("%f", value);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const double Double::Min = DBL_MIN;
    const double Double::Max = DBL_MAX;

    double Double::Parse(const char* s, int /*length*/)
    {
        if (s)
            return static_cast<double>(std::atof(s));
        else
            return 0.0;        
    }

    String Double::ToString(double value)
    {
        return String::CFormat("%.lf", value);
    }
}