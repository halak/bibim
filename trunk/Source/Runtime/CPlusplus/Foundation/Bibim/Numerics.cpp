#include <Bibim/PCH.h>
#include <Bibim/Numerics.h>
#include <limits>
#include <stdlib.h>

namespace Bibim
{
    const char Char::Min = std::numeric_limits<char>::min();
    const char Char::Max = std::numeric_limits<char>::max();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const uchar UChar::Min = std::numeric_limits<uchar>::min();
    const uchar UChar::Max = std::numeric_limits<uchar>::max();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const short Short::Min = std::numeric_limits<short>::min();
    const short Short::Max = std::numeric_limits<short>::max();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const ushort UShort::Min = std::numeric_limits<ushort>::min();
    const ushort UShort::Max = std::numeric_limits<ushort>::max();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const int Int::Min = std::numeric_limits<int>::min();
    const int Int::Max = std::numeric_limits<int>::max();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const uint UInt::Min = std::numeric_limits<uint>::min();
    const uint UInt::Max = std::numeric_limits<uint>::max();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const long Long::Min = std::numeric_limits<long>::min();
    const long Long::Max = std::numeric_limits<long>::max();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const ulong ULong::Min = std::numeric_limits<ulong>::min();
    const ulong ULong::Max = std::numeric_limits<ulong>::max();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const float Float::Min = std::numeric_limits<float>::min();
    const float Float::Max = std::numeric_limits<float>::max();
    const float Float::NaN = std::numeric_limits<float>::quiet_NaN();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const double Double::Min = std::numeric_limits<double>::min();
    const double Double::Max = std::numeric_limits<double>::max();
    const double Double::NaN = std::numeric_limits<double>::quiet_NaN();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const int64 Int64::Min = std::numeric_limits<int64>::min();
    const int64 Int64::Max = std::numeric_limits<int64>::max();

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    const uint64 UInt64::Min = std::numeric_limits<uint64>::min();
    const uint64 UInt64::Max = std::numeric_limits<uint64>::max();
}