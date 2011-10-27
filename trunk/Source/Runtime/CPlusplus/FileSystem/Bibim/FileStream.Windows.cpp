#include <Bibim/PCH.h>
#include <Bibim/FileStream.Windows.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   include <windows.h>

    namespace Bibim
    {
        FileStream::FileStream(const String& path, AccessMode accessMode)
            : handle(nullptr),
              canRead(false),
              canWrite(false)
        {
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

            handle = ::CreateFile(path.CStr(), windowsAccessMode, FILE_SHARE_READ, nullptr, windowsCreationDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);
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
            if (handle == INVALID_HANDLE_VALUE || size < 0 || CanRead() == false)
                return -1;
            if (size == 0)
                return 0;

            DWORD readBytes = 0;
            ::ReadFile(handle, buffer, size, &readBytes, nullptr);

            return static_cast<int>(readBytes);
        }

        int FileStream::Write(const void* buffer, int size)
        {
            if (handle == INVALID_HANDLE_VALUE || size < 0 || CanWrite() == false)
                return -1;
            if (size == 0)
                return 0;

            DWORD writtenBytes = 0;
            ::WriteFile(handle, buffer, size, &writtenBytes, nullptr);

            return static_cast<int>(writtenBytes);
        }

        void FileStream::Flush()
        {
            if (handle == INVALID_HANDLE_VALUE || CanWrite() == false)
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
            return static_cast<int>(::GetFileSize(handle, nullptr));
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