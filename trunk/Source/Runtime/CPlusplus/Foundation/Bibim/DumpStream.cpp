#include <Bibim/PCH.h>
#include <Bibim/DumpStream.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    DumpStream::DumpStream(Stream* baseStream, Stream* outputStream)
        : baseStream(baseStream),
          outputStream(outputStream)
    {
        BBAssert(baseStream);
        BBAssert(outputStream);
    }

    DumpStream::~DumpStream()
    {
    }

    int DumpStream::Read(void* buffer, int size)
    {
        const int result = baseStream->Read(buffer, size);
        outputStream->Write(buffer, result);
        return result;
    }

    int DumpStream::Write(const void* buffer, int size)
    {
        const int result = baseStream->Write(buffer, size);
        outputStream->Write(buffer, result);
        return result;
    }

    void DumpStream::Flush()
    {
        baseStream->Flush();
    }

    int DumpStream::Seek(int offset, SeekOrigin origin)
    {
        return baseStream->Seek(offset, origin);
    }

    int DumpStream::GetPosition()
    {
        return baseStream->GetPosition();
    }

    int DumpStream::GetLength()
    {
        return baseStream->GetLength();
    }

    bool DumpStream::CanRead() const
    {
        return baseStream->CanRead();
    }

    bool DumpStream::CanWrite() const
    {
        return baseStream->CanWrite();
    }

    bool DumpStream::CanSeek() const
    {
        return baseStream->CanSeek();
    }
}