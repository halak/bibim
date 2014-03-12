#include <Bibim/Config.h>
#include <Bibim/ForkStream.h>
#include <Bibim/Assert.h>
#include <Bibim/Math.h>

namespace Bibim
{
    ForkStream::ForkStream(Stream* stream1, Stream* stream2, Stream* stream3, Stream* stream4)
    {
        if (stream1)
            streams.push_back(stream1);
        if (stream2)
            streams.push_back(stream2);
        if (stream3)
            streams.push_back(stream3);
        if (stream4)
            streams.push_back(stream4);
    }

    ForkStream::~ForkStream()
    {
    }

    int ForkStream::Read(void* buffer, int size)
    {
        return 0;
    }

    int ForkStream::Write(const void* buffer, int size)
    {
        int writtenSize = 0;
        for (StreamCollection::const_iterator it = streams.begin(); it != streams.end(); ++it)
        {
            writtenSize = Math::Min((*it)->Write(buffer, size), writtenSize);
        }

        return writtenSize;
    }

    void ForkStream::Flush()
    {
        for (StreamCollection::const_iterator it = streams.begin(); it != streams.end(); ++it)
            (*it)->Flush();
    }

    int ForkStream::Seek(int offset, SeekOrigin origin)
    {
        return 0;
    }

    int ForkStream::GetPosition()
    {
        return 0;
    }

    int ForkStream::GetLength()
    {
        return 0;
    }

    bool ForkStream::CanRead() const
    {
        return false;
    }

    bool ForkStream::CanWrite() const
    {
        for (StreamCollection::const_iterator it = streams.begin(); it != streams.end(); ++it)
        {
            if ((*it)->CanWrite() == false)
                return false;
        }

        return true;
    }

    bool ForkStream::CanSeek() const
    {
        return false;
    }
}