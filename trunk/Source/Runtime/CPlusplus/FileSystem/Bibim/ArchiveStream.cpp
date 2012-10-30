#include <Bibim/PCH.h>
#include <Bibim/ArchiveStream.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>
# include <windows.h>

namespace Bibim
{
    ArchiveStream::ArchiveStream()
    {
    }

    ArchiveStream::~ArchiveStream()
    {
        Close();
    }

    void ArchiveStream::Close()
    {
    }

    int ArchiveStream::Read(void* buffer, int size)
    {
    }

    int ArchiveStream::Write(const void* buffer, int size)
    {
    }

    void ArchiveStream::Flush()
    {
    }

    int ArchiveStream::Seek(int offset, SeekOrigin origin)
    {
        return 0;
    }

    int ArchiveStream::GetPosition()
    {
        return 0;
    }

    int ArchiveStream::GetLength()
    {
        return 0;
    }

    bool ArchiveStream::CanRead() const
    {
        return false;
    }

    bool ArchiveStream::CanWrite() const
    {
        return false;
    }

    bool ArchiveStream::CanSeek() const
    {
        return false;
    }
}