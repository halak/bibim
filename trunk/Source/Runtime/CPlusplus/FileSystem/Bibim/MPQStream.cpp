#include <Bibim/PCH.h>
#include <Bibim/MPQStream.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>
# include <windows.h>

namespace Bibim
{
    MPQStream::MPQStream()
    {
    }

    MPQStream::~MPQStream()
    {
        Close();
    }

    void MPQStream::Close()
    {
    }

    int MPQStream::Read(void* buffer, int size)
    {
        return 0;
    }

    int MPQStream::Write(const void* buffer, int size)
    {
        return 0;
    }

    void MPQStream::Flush()
    {
    }

    int MPQStream::Seek(int offset, SeekOrigin origin)
    {
        return 0;
    }

    int MPQStream::GetPosition()
    {
        return 0;
    }

    int MPQStream::GetLength()
    {
        return 0;
    }

    bool MPQStream::CanRead() const
    {
        return false;
    }

    bool MPQStream::CanWrite() const
    {
        return false;
    }

    bool MPQStream::CanSeek() const
    {
        return false;
    }
}