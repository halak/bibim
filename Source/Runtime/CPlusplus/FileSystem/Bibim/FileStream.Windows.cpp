#include <Bibim/PCH.h>
#include <Bibim/FileStream.h>
#include <Bibim/Math.h>
#include <Bibim/Number.h>
#include <vector>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   include <windows.h>

    namespace Bibim
    {
        static const std::vector<byte>::size_type DefaultFileStreamCacheSize = 1024 * 8;

        struct FileStream::Fields
        {
            HANDLE Handle;

            int position;
            int size;
            uint64 position64;
            uint64 size64;

            std::vector<byte> Cache;
            int CacheOffset;
            int CachedSize;

            bool CanRead;
            bool CanWrite;
        };

        FileStream::FileStream(const String& path, FileAccess::E access, FileShare::E shareMode)
            : mPointer(new Fields()),
              m(*mPointer)
        {
            DWORD windowsAccess = 0x00000000;
            if (access == FileAccess::Read)
                windowsAccess = GENERIC_READ;
            else if (access == FileAccess::Write)
                windowsAccess = GENERIC_WRITE;
            DWORD windowsShareMode = 0x00000000;
            if (shareMode & FileShare::Read)
                windowsShareMode = FILE_SHARE_READ;
            if (shareMode & FileShare::Write)
                windowsShareMode = FILE_SHARE_WRITE;
            if (shareMode & FileShare::Delete)
                windowsShareMode = FILE_SHARE_DELETE;
            DWORD windowsCreationDisposition = 0x00000000;
            if (windowsAccess == GENERIC_READ)
                windowsCreationDisposition = OPEN_EXISTING;
            else if (windowsAccess & GENERIC_WRITE)
                windowsCreationDisposition = CREATE_NEW;

            m.Handle = CreateFile(path.CStr(), windowsAccess, windowsShareMode, nullptr, windowsCreationDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (m.Handle == INVALID_HANDLE_VALUE)
            {
                m.CanRead  = false;
                m.CanWrite = false;
                return;
            }

            m.Cache.resize(DefaultFileStreamCacheSize);
            m.CanRead  = access == FileAccess::Read;
            m.CanWrite = access == FileAccess::Write;

            DWORD sizeHigh = 0;
            DWORD sizeLow = GetFileSize(m.Handle, &sizeHigh);
            m.position = 0;
            m.size     = sizeHigh == 0 ? static_cast<int>(sizeLow) : Number::MaxInt;
            m.position64 = 0;
            m.size64     = (static_cast<uint64>(sizeHigh) << 32) | (static_cast<uint64>(sizeLow) << 0);

            if (m.CanRead)
                StoreCache();
        }

        FileStream::~FileStream()
        {
            Close();
            delete mPointer;
        }

        void FileStream::Close()
        {
            if (m.Handle != INVALID_HANDLE_VALUE)
            {
                Flush();
                CloseHandle(m.Handle);
                m.Handle = INVALID_HANDLE_VALUE;
            }
        }

        int FileStream::Read(void* buffer, int size)
        {
            if (m.Handle == INVALID_HANDLE_VALUE || size < 0 || CanRead() == false)
                return -1;
            if (size == 0)
                return 0;

            byte* castedBuffer = static_cast<byte*>(buffer);
            if (m.CacheOffset + size < m.CachedSize)
            {
                const int end = m.CacheOffset + size;
                for (int i = m.CacheOffset; i < end; i++, castedBuffer++)
                    castedBuffer[0] = m.Cache[i];

                m.position   += size;
                m.position64 += static_cast<uint64>(size);
                m.CacheOffset = end;
                return size;
            }
            else
            {
                int remainingSize = size;

                while (remainingSize > 0 && m.CachedSize > 0)
                {
                    const int end = Math::Min(m.CacheOffset + remainingSize, m.CachedSize);
                    for (int i = m.CacheOffset; i < end; i++, castedBuffer++)
                        castedBuffer[0] = m.Cache[i];

                    remainingSize -= (end - m.CacheOffset);

                    StoreCache();
                }

                const int result = size - remainingSize;
                m.position   += result;
                m.position64 += static_cast<uint64>(result);
                return result;
            }
        }

        int FileStream::Write(const void* buffer, int size)
        {
            if (m.Handle == INVALID_HANDLE_VALUE || size < 0 || CanWrite() == false)
                return -1;
            if (size == 0)
                return 0;

            const byte* castedBuffer = static_cast<const byte*>(buffer);
            if (m.CacheOffset + size < m.CachedSize)
            {
                const int end = m.CacheOffset + size;
                for (int i = m.CacheOffset; i < end; i++, castedBuffer++)
                    m.Cache[i] = castedBuffer[0];

                m.position   += size;
                m.position64 += static_cast<uint64>(size);
                m.size       += size;
                m.size64     += static_cast<uint64>(size);
                return size;
            }
            else
            {
                int remainingSize = size;

                while (remainingSize > 0 && m.CachedSize > 0)
                {
                    // ¹Ì±¸Çö
                }

                const int result = size - remainingSize;
                m.position   += result;
                m.position64 += static_cast<uint64>(result);
                m.size       += result;
                m.size64     += static_cast<uint64>(result);
                return result;
            }
        }

        void FileStream::Flush()
        {
            if (m.Handle == INVALID_HANDLE_VALUE || CanWrite() == false)
                return;

            DWORD writtenSize = 0;
            if (WriteFile(m.Handle, &m.Cache[0], static_cast<DWORD>(m.Cache.size()), &writtenSize, nullptr))
            {
                m.CacheOffset = 0;
                m.CachedSize = static_cast<int>(m.Cache.size());
            }
            else
            {
            }
        }

        int FileStream::GetPosition() const
        {
            return m.position;
        }

        int FileStream::GetSize() const
        {
            return m.size;
        }

        uint64 FileStream::GetPosition64() const
        {
            return m.position64;
        }

        uint64 FileStream::GetSize64() const
        {
            return m.size64;
        }

        bool FileStream::CanRead() const
        {
            return m.CanRead;
        }

        bool FileStream::CanWrite() const
        {
            return m.CanWrite;
        }

        void FileStream::StoreCache()
        {
            DWORD readSize = 0;
            if (ReadFile(m.Handle, &m.Cache[0], static_cast<DWORD>(m.Cache.size()), &readSize, nullptr))
            {
                m.CacheOffset = 0;
                m.CachedSize = static_cast<int>(readSize);
            }
            else
            {
            }
        }
    }

#endif