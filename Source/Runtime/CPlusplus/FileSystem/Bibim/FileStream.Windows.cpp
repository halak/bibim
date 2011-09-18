#include <Bibim/PCH.h>
#include <Bibim/FileStream.Windows.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   include <windows.h>

    namespace Bibim
    {
        static const std::vector<byte>::size_type DefaultFileStreamCacheSize = 1024 * 8;

        FileStream::FileStream(const String& path, AccessMode accessMode)
            : handle(nullptr),
              position(0),
              size(0),
              position64(0),
              size64(0),
              cacheOffset(0),
              cacheSize(0),
              canRead(false),
              canWrite(false)
        {
            DWORD windowsAccessMode = 0x00000000;
            if (accessMode == ReadOnly)
                windowsAccessMode = GENERIC_READ;
            else if (accessMode == WriteOnly)
                windowsAccessMode = GENERIC_WRITE;

            DWORD windowsShareMode = 0x00000000;
            if (windowsAccessMode == GENERIC_READ)
                windowsShareMode = FILE_SHARE_READ;
            
            DWORD windowsCreationDisposition = 0x00000000;
            if (windowsAccessMode == GENERIC_READ)
                windowsCreationDisposition = OPEN_EXISTING;
            else if (windowsAccessMode & GENERIC_WRITE)
                windowsCreationDisposition = CREATE_NEW;

            handle = CreateFile(path.CStr(), windowsAccessMode, windowsShareMode, nullptr, windowsCreationDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (handle == INVALID_HANDLE_VALUE)
            {
                canRead  = false;
                canWrite = false;
                return;
            }

            cache.resize(DefaultFileStreamCacheSize);
            canRead  = (accessMode == FileStream::ReadOnly);
            canWrite = (accessMode == FileStream::WriteOnly);

            DWORD sizeHigh = 0;
            DWORD sizeLow = GetFileSize(handle, &sizeHigh);
            position = 0;
            size     = sizeHigh == 0 ? static_cast<int>(sizeLow) : Int::Max;
            position64 = 0;
            size64     = (static_cast<uint64>(sizeHigh) << 32) | (static_cast<uint64>(sizeLow) << 0);

            if (canRead)
                StoreCache();
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
                CloseHandle(handle);
                handle = INVALID_HANDLE_VALUE;
            }
        }

        int FileStream::Read(void* buffer, int size)
        {
            if (handle == INVALID_HANDLE_VALUE || size < 0 || CanRead() == false)
                return -1;
            if (size == 0)
                return 0;

            byte* castedBuffer = static_cast<byte*>(buffer);
            if (cacheOffset + size < cacheSize)
            {
                const int end = cacheOffset + size;
                for (int i = cacheOffset; i < end; i++, castedBuffer++)
                    castedBuffer[0] = cache[i];

                position   += size;
                position64 += static_cast<uint64>(size);
                cacheOffset = end;
                return size;
            }
            else
            {
                int remainingSize = size;

                while (remainingSize > 0 && cacheSize > 0)
                {
                    const int end = Math::Min(cacheOffset + remainingSize, cacheSize);
                    for (int i = cacheOffset; i < end; i++, castedBuffer++)
                        castedBuffer[0] = cache[i];

                    remainingSize -= (end - cacheOffset);

                    StoreCache();
                }

                const int result = size - remainingSize;
                position   += result;
                position64 += static_cast<uint64>(result);
                return result;
            }
        }

        int FileStream::Write(const void* buffer, int size)
        {
            if (handle == INVALID_HANDLE_VALUE || size < 0 || CanWrite() == false)
                return -1;
            if (size == 0)
                return 0;

            const byte* castedBuffer = static_cast<const byte*>(buffer);
            if (cacheOffset + size < cacheSize)
            {
                const int end = cacheOffset + size;
                for (int i = cacheOffset; i < end; i++, castedBuffer++)
                    cache[i] = castedBuffer[0];

                position   += size;
                position64 += static_cast<uint64>(size);
                size       += size;
                size64     += static_cast<uint64>(size);
                return size;
            }
            else
            {
                int remainingSize = size;

                while (remainingSize > 0 && cacheSize > 0)
                {
                    // ¹Ì±¸Çö
                }

                const int result = size - remainingSize;
                position   += result;
                position64 += static_cast<uint64>(result);
                size       += result;
                size64     += static_cast<uint64>(result);
                return result;
            }
        }

        void FileStream::Flush()
        {
            if (handle == INVALID_HANDLE_VALUE || CanWrite() == false)
                return;

            DWORD writtenSize = 0;
            if (WriteFile(handle, &cache[0], static_cast<DWORD>(cache.size()), &writtenSize, nullptr))
            {
                cacheOffset = 0;
                cacheSize = static_cast<int>(cache.size());
            }
            else
            {
            }
        }

        int FileStream::GetPosition() const
        {
            return position;
        }

        int FileStream::GetSize() const
        {
            return size;
        }

        uint64 FileStream::GetPosition64() const
        {
            return position64;
        }

        uint64 FileStream::GetSize64() const
        {
            return size64;
        }

        bool FileStream::CanRead() const
        {
            return canRead;
        }

        bool FileStream::CanWrite() const
        {
            return canWrite;
        }

        void FileStream::StoreCache()
        {
            DWORD readSize = 0;
            if (ReadFile(handle, &cache[0], static_cast<DWORD>(cache.size()), &readSize, nullptr))
            {
                cacheOffset = 0;
                cacheSize = static_cast<int>(readSize);
            }
            else
            {
            }
        }
    }

#endif