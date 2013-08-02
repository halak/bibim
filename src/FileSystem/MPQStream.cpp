#include <Bibim/Config.h>
#include <Bibim/MPQStream.h>
#include <Bibim/MPQ.h>
#include <StormLib.h>

namespace Bibim
{
    MPQStream::MPQStream(MPQ* mpq, const String& path)
        : handle(nullptr)
    {
        if (mpq == nullptr || mpq->GetHandle() == nullptr)
            return;

        HANDLE internalHandle = NULL;
        if (SFileOpenFileEx(mpq->GetHandle(), path.CStr(), SFILE_OPEN_FROM_MPQ, &internalHandle))
            handle = internalHandle;
    }

    MPQStream::~MPQStream()
    {
        Close();
    }

    void MPQStream::Close()
    {
        if (handle != nullptr)
        {
            SFileCloseFile(handle);
            handle = nullptr;
        }
    }

    int MPQStream::Read(void* buffer, int size)
    {
        if (handle == nullptr || size <= 0)
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
        if (handle != nullptr)
            return static_cast<int>(::SFileSetFilePointer(handle, 0, nullptr, FILE_CURRENT));
        else
            return 0;
    }

    int MPQStream::GetLength()
    {
        if (handle != nullptr)
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