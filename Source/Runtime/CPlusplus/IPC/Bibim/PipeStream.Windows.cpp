#include <Bibim/PCH.h>
#include <Bibim/PipeStream.h>

namespace Bibim
{
    PipeStream::PipeStream(const String& name, AccessMode accessMode)
        : handle(NULL),
          name(name),
          accessMode(accessMode)
    {
    }

    PipeStream::~PipeStream()
    {
        if (handle != NULL)
        {
            ::CloseHandle(handle);
            handle = NULL;
        }
    }

    int PipeStream::Read(void* buffer, int size)
    {
        return 0;
    }

    int PipeStream::Write(const void* buffer, int size)
    {
        return 0;
    }

    void PipeStream::Flush()
    {
        ::FlushFileBuffers(handle);
    }

    bool PipeStream::CanRead() const
    {
        return accessMode == ReadOnly || accessMode == ReadAndWrite;
    }

    bool PipeStream::CanWrite() const
    {
        return accessMode == WriteOnly || accessMode == ReadAndWrite;
    }
}