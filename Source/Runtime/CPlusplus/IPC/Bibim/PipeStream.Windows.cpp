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
        BBAssertDebug(size >= 0);

        DWORD read = 0;
        if (handle && size > 0 && ::ReadFile(handle, buffer, size, &read, NULL))
            return static_cast<int>(read);
        else
            return 0;
    }

    int PipeStream::Write(const void* buffer, int size)
    {
        BBAssertDebug(size >= 0);

        DWORD written = 0;
        if (handle && size > 0 && ::WriteFile(handle, buffer, size, &written, NULL))
            return static_cast<int>(written);
        else
            return 0;
    }

    int64 PipeStream::Seek(int64 /*offset*/, SeekOrigin /*origin*/)
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

    bool PipeStream::CanSeek() const
    {
        return false;
    }
}