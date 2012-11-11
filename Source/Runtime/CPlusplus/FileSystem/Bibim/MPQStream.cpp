#include <Bibim/PCH.h>
#include <Bibim/MPQStream.h>
#include <Bibim/MPQ.h>
#include <StormLib.h>

namespace Bibim
{
    MPQStream::MPQStream(MPQ* mpq, const String& path)
        : handle(INVALID_HANDLE_VALUE)
    {
        if (mpq == nullptr || mpq->GetHandle() == INVALID_HANDLE_VALUE)
            return;

        HANDLE win32Handle = NULL;
        if (SFileOpenFileEx(mpq->GetHandle(), path.CStr(), SFILE_OPEN_FROM_MPQ, &win32Handle))
            handle = win32Handle;
    }

    MPQStream::~MPQStream()
    {
        Close();
    }

    void MPQStream::Close()
    {
        if (handle != INVALID_HANDLE_VALUE)
        {
            SFileCloseFile(handle);
            handle = INVALID_HANDLE_VALUE;
        }
    }

    int MPQStream::Read(void* buffer, int size)
    {
        if (handle == INVALID_HANDLE_VALUE || size <= 0)
            return 0;

        DWORD readBytes = 0;
        SFileReadFile(handle, buffer, size, &readBytes, nullptr);

        return static_cast<int>(readBytes);
    }

    int MPQStream::Write(const void* /*buffer*/, int /*size*/)
    {
        return 0;
    }

    void MPQStream::Flush()
    {
    }

    int MPQStream::Seek(int offset, SeekOrigin origin)
    {
        DWORD moveMethod = 0;
        switch (origin)
        {
            case FromBegin:
                moveMethod = FILE_BEGIN;
                break;
            case FromEnd:
                moveMethod = FILE_END;
                break;
            case FromCurrent:
                moveMethod = FILE_CURRENT;
                break;
        }

        return static_cast<int>(::SFileSetFilePointer(handle, offset, nullptr, moveMethod));
    }

    int MPQStream::GetPosition()
    {
        if (handle != INVALID_HANDLE_VALUE)
            return static_cast<int>(::SFileSetFilePointer(handle, 0, nullptr, FILE_CURRENT));
        else
            return 0;
    }

    int MPQStream::GetLength()
    {
        if (handle != INVALID_HANDLE_VALUE)
            return SFileGetFileSize(handle, nullptr);
        else
            return 0;
    }

    bool MPQStream::CanRead() const
    {
        return true;
    }

    bool MPQStream::CanWrite() const
    {
        return false;
    }

    bool MPQStream::CanSeek() const
    {
        return true;
    }
}