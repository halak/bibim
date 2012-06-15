#include <Bibim/PCH.h>
#include <Bibim/FileStream.CRT.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>
#include <cstdlib>

namespace Bibim
{
    FileStream::FileStream(const String& path, AccessMode accessMode)
        : handle(nullptr),
          canRead(false),
          canWrite(false)
    {
        const char* crtAccessMode = nullptr;
        if (accessMode == ReadOnly)
            crtAccessMode = "rb";
        else if (accessMode == WriteOnly)
            crtAccessMode = "wb";

        handle = std::fopen(path.CStr(), crtAccessMode);
        if (handle == nullptr)
        {
            canRead = false;
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
        if (handle != nullptr)
        {
            Flush();
            std::fclose(static_cast<FILE*>(handle));
            handle = nullptr;
        }
    }

    int FileStream::Read(void* buffer, int size)
    {
        if (handle == nullptr || size < 0 || canRead == false)
            return -1;
        if (size == 0)
            return 0;

        return static_cast<int>(std::fread(buffer, 1, size, static_cast<FILE*>(handle)));
    }

    int FileStream::Write(const void* buffer, int size)
    {
        if (handle == nullptr || size < 0 || canWrite == false)
            return -1;
        if (size == 0)
            return 0;

        return static_cast<int>(std::fwrite(buffer, 1, size, static_cast<FILE*>(handle)));
    }

    void FileStream::Flush()
    {
        if (handle == nullptr || canWrite == false)
            return;

        std::fflush(static_cast<FILE*>(handle));
    }

    int FileStream::Seek(int offset, SeekOrigin origin)
    {
        int crtOrigin = 0;
        switch (origin)
        {
            case FromBegin:
                crtOrigin = SEEK_SET;
                break;
            case FromEnd:
                crtOrigin = SEEK_END;
                break;
            case FromCurrent:
                crtOrigin = SEEK_CUR;
                break;
        }

        std::fseek(static_cast<FILE*>(handle), offset, crtOrigin);
        return static_cast<int>(std::ftell(static_cast<FILE*>(handle)));
    }

    int FileStream::GetPosition()
    {
        return static_cast<int>(std::ftell(static_cast<FILE*>(handle)));
    }

    int FileStream::GetLength()
    {
        const long originalPositoin = std::ftell(static_cast<FILE*>(handle));
        std::fseek(static_cast<FILE*>(handle), 0, SEEK_END);
        const long result = std::ftell(static_cast<FILE*>(handle));
        std::fseek(static_cast<FILE*>(handle), originalPositoin, SEEK_SET);

        return static_cast<int>(result);
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