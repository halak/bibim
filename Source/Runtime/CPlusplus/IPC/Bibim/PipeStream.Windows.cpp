#include <Bibim/PCH.h>
#include <Bibim/PipeStream.h>

namespace Bibim
{
    PipeStream::PipeStream()
        : handle(INVALID_HANDLE_VALUE),
          name(String::Empty),
          accessMode(ReadOnly)
    {
    }

    PipeStream::~PipeStream()
    {
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

    void PipeStream::Initialize(HANDLE handle, const String& name, AccessMode accessMode)
    {
        this->handle = handle;
        this->name = name;
        this->accessMode = accessMode;
    }

    void PipeStream::Finalize()
    {
        if (handle != INVALID_HANDLE_VALUE && handle != NULL)
            ::CloseHandle(handle);

        handle = INVALID_HANDLE_VALUE;
        name = String::Empty;
        accessMode = ReadOnly;
    }
}