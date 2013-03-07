#include <Bibim/PCH.h>
#include <Bibim/FileStream.Android.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>
#include <Bibim/Log.h>

namespace Bibim
{
    static AAssetManager* Assets = nullptr;

    FileStream::FileStream(const String& path, AccessMode accessMode)
        : handle(nullptr),
          canRead(false),
          canWrite(false)
    {
        if (Assets == nullptr || accessMode != ReadOnly)
            return;

        String cleanPath = path;
        cleanPath.Replace('\\', '/');
        handle = AAssetManager_open(Assets, cleanPath.CStr(), AASSET_MODE_UNKNOWN);
        if (handle == nullptr)
        {
            canRead  = false;
            canWrite = false;
            return;
        }

        canRead  = (accessMode == ReadOnly);
        canWrite = (accessMode == WriteOnly);
    }

    FileStream::~FileStream()
    {
        Close();
    }

    void FileStream::Close()
    {
        if (handle)
        {
            AAsset_close(handle);
            handle = nullptr;
        }
    }

    int FileStream::Read(void* buffer, int size)
    {
        if (handle == nullptr || size <= 0 || canRead == false)
            return 0;

        return static_cast<int>(AAsset_read(handle, buffer, size));
    }

    int FileStream::Write(const void* buffer, int size)
    {
        return 0;
    }

    void FileStream::Flush()
    {
    }

    int FileStream::Seek(int offset, SeekOrigin origin)
    {
        int seekOrigin = 0;
        switch (origin)
        {
            case FromBegin:
                seekOrigin = SEEK_SET;
                break;
            case FromEnd:
                seekOrigin = SEEK_CUR;
                break;
            case FromCurrent:
                seekOrigin = SEEK_END;
                break;
        }

        return static_cast<int>(AAsset_seek(handle, static_cast<int>(offset), seekOrigin));
    }

    int FileStream::GetPosition()
    {
        return static_cast<int>(AAsset_seek(handle, 0, SEEK_CUR));
    }

    int FileStream::GetLength()
    {
        return static_cast<int>(AAsset_getLength(handle));
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

    void FileStream::SetAssets(AAssetManager* value)
    {
        Assets = value;
    }
}