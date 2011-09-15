#include <Bibim/MemoryStream.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    MemoryStream::MemoryStream()
        : buffer(nullptr),
          length(0),
          position(0)
    {
    }

    MemoryStream::MemoryStream(int length)
        : buffer(nullptr),
          length(length),
          position(0)
    {
        if (length > 0)
            buffer = new byte[length];
    }

    MemoryStream::MemoryStream(byte* buffer, int length)
        : buffer(buffer),
          length(length),
          position(position)
    {
    }

    MemoryStream::~MemoryStream()
    {
    }

    int MemoryStream::Read(void* /*buffer*/, int /*size*/)
    {
        throw;
    }

    int MemoryStream::Write(const void* /*buffer*/, int /*size*/)
    {
        throw;
    }

    void MemoryStream::Flush()
    {
    }

    int MemoryStream::Seek(int offset, SeekOrigin origin)
    {
        switch (origin)
        {
            case FromBegin:
                position = offset;
                break;
            case FromEnd:
                position = length + offset;
                break;
            case FromCurrent:
                position += offset;
                break;
            default:
                BBBreak();
                break;
        }

        return position;
    }

    int MemoryStream::GetPosition()
    {
        return position;
    }

    int MemoryStream::GetLength()
    {
        return length;
    }

    bool MemoryStream::CanRead() const
    {
        return true;
    }

    bool MemoryStream::CanWrite() const
    {
        return true;
    }

    bool MemoryStream::CanSeek() const
    {
        return true;
    }
}