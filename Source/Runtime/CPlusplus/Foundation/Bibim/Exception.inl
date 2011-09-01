#include <Bibim/NullPointer.h>

namespace Bibim
{
    Exception::Exception()
        : Message(nullptr)
    {
    }

    Exception::Exception(const char* message)
        : Message(message)
    {
    }

    Exception::Exception(const Exception& original)
        : Message(original.Message)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    BadArgumentException::BadArgumentException()
        : Exception(),
          ArgumentName(nullptr)
    {
    }

    BadArgumentException::BadArgumentException(const char* argumentName)
        : Exception(),
          ArgumentName(argumentName)
    {
    }

    BadArgumentException::BadArgumentException(const char* argumentName, const char* message)
        : Exception(message),
          ArgumentName(argumentName)
    {
    }

    BadArgumentException::BadArgumentException(const BadArgumentException& original)
        : Exception(original),
          ArgumentName(original.ArgumentName)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    BadCastException::BadCastException()
        : Exception()
    {
    }

    BadCastException::BadCastException(const char* message)
        : Exception(message)
    {
    }

    BadCastException::BadCastException(const BadCastException& original)
        : Exception(original)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    NotSupportedException::NotSupportedException()
        : Exception()
    {
    }

    NotSupportedException::NotSupportedException(const char* message)
        : Exception(message)
    {
    }

    NotSupportedException::NotSupportedException(const NotSupportedException& original)
        : Exception(original)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    OutOfRangeException::OutOfRangeException()
        : Exception(),
          Index(-1),
          Count(0)
    {
    }

    OutOfRangeException::OutOfRangeException(const char* message, int index, int count)
        : Exception(message),
          Index(index),
          Count(count)
    {
    }

    OutOfRangeException::OutOfRangeException(const OutOfRangeException& original)
        : Exception(original)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    InvalidOperationException::InvalidOperationException()
        : Exception()
    {
    }

    InvalidOperationException::InvalidOperationException(const char* message)
        : Exception(message)
    {
    }

    InvalidOperationException::InvalidOperationException(const InvalidOperationException& original)
        : Exception(original)
    {
    }
}