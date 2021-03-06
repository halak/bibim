﻿#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_WINDOWS))

#include <Bibim/FileStream.Windows.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>
#include <Bibim/Path.h>
#include <windows.h>

namespace Bibim
{
    FileStream::FileStream(const String& path, AccessMode accessMode)
        : handle(nullptr),
          canRead(false),
          canWrite(false)
    {
        String p = path;
        p.Replace('\\', '/');
        //BBAssert(path.Contains('\\') == false);

        DWORD windowsAccessMode = 0x00000000;
        if (accessMode == ReadOnly)
            windowsAccessMode = GENERIC_READ;
        else if (accessMode == WriteOnly)
            windowsAccessMode = GENERIC_WRITE;

        DWORD windowsCreationDisposition = 0x00000000;
        if (windowsAccessMode == GENERIC_READ)
            windowsCreationDisposition = OPEN_EXISTING;
        else if (windowsAccessMode & GENERIC_WRITE)
            windowsCreationDisposition = CREATE_ALWAYS;

        handle = ::CreateFile(p.CStr(), windowsAccessMode, FILE_SHARE_READ,
                              nullptr, windowsCreationDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (handle == INVALID_HANDLE_VALUE)
        {
            if (accessMode == WriteOnly)
            {
                const String directory = Path::GetDirectory(p);
                if (directory.IsEmpty() == false &&
                    ::CreateDirectory(directory.CStr(), nullptr))
                {
                    handle = ::CreateFile(p.CStr(),
                                          windowsAccessMode,
                                          FILE_SHARE_READ,
                                          nullptr,
                                          windowsCreationDisposition,
                                          FILE_ATTRIBUTE_NORMAL,
                                          nullptr);
                }
            }
        }
        
        if (handle == INVALID_HANDLE_VALUE)
        {
            canRead  = false;
            canWrite = false;
            return;
        }

        canRead  = (accessMode == FileStream::ReadOnly);
        canWrite = (accessMode == FileStream::WriteOnly);
    }

    FileStream::~FileStream()
    {
        Close();
    }

    void FileStream::Close()
    {
        if (handle != INVALID_HANDLE_VALUE)
        {
            Flush();
            ::CloseHandle(handle);
            handle = INVALID_HANDLE_VALUE;
        }
    }

    int FileStream::Read(void* buffer, int size)
    {
        if (handle == INVALID_HANDLE_VALUE || size <= 0 || canRead == false)
            return 0;

        DWORD readBytes = 0;
        ::ReadFile(handle, buffer, size, &readBytes, nullptr);

        return static_cast<int>(readBytes);
    }

    int FileStream::Write(const void* buffer, int size)
    {
        if (handle == INVALID_HANDLE_VALUE || size <= 0 || canWrite == false)
            return 0;

        DWORD writtenBytes = 0;
        ::WriteFile(handle, buffer, size, &writtenBytes, nullptr);

        return static_cast<int>(writtenBytes);
    }

    void FileStream::Flush()
    {
        if (handle == INVALID_HANDLE_VALUE || canWrite == false)
            return;

        ::FlushFileBuffers(handle);
    }

    int FileStream::Seek(int offset, SeekOrigin origin)
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

        return static_cast<int>(::SetFilePointer(handle, offset, nullptr, moveMethod));
    }

    int FileStream::GetPosition()
    {
        return static_cast<int>(::SetFilePointer(handle, 0, nullptr, FILE_CURRENT));
    }

    int FileStream::GetLength()
    {
        if (handle != INVALID_HANDLE_VALUE)
            return static_cast<int>(::GetFileSize(handle, nullptr));
        else
            return 0;
    }

    bool FileStream::CanRead() const
    {
        return canRead;
    }

    bool FileStream::CanWrite() const
    {
        return canWrite;
    }

    bool FileStream::CanSeek() const
    {
        return true;
    }
}

#endif