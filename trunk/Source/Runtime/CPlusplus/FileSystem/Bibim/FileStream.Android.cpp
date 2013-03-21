#include <Bibim/PCH.h>
#include <Bibim/FileStream.Android.h>
#include <Bibim/Assert.h>
#include <Bibim/Environment.h>
#include <Bibim/Math.h>
#include <Bibim/Numerics.h>
#include <Bibim/Log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

namespace Bibim
{
    static AAssetManager* Assets = nullptr;

    static bool IsAbsolutePath(const String& path)
    {
        if (path.GetLength() >= 2)
        {
            const char* s = path.CStr();
            return (s[0] == '/' ||
                    s[1] == ':' ||
                    s[2] == ':');
        }

        return false;
    }

    FileStream::FileStream(const String& path, AccessMode accessMode)
        : handle(nullptr),
          asset(nullptr),
          length(-1),
          canRead(false),
          canWrite(false)
    {
        if (path.IsEmpty())
            return;

        char mode[3] = { 'r', 'b', '\0' };
        if (accessMode == ReadOnly)
            mode[0] = 'r';
        else if (accessMode == WriteOnly)
            mode[0] = 'w';

        String cleanPath = path;
        cleanPath.Replace('\\', '/');

        String absPath;
        if (IsAbsolutePath(cleanPath) == false)
        {
            BBAssert(cleanPath.CStr()[0] != '/');
            absPath = Environment::GetWorkingDirectory() + cleanPath;
        }
        else
            absPath = cleanPath;

        handle = std::fopen(absPath.CStr(), mode);
        if (handle == nullptr)
        {
            canRead  = false;
            canWrite = false;

            if (accessMode != ReadOnly)
                return;
            if (Assets == nullptr)
                return;

            // 읽기 전용으로 열 경우에는 Asset도 한 번 살펴봅니다.
            asset = AAssetManager_open(Assets, cleanPath.CStr(), AASSET_MODE_UNKNOWN);
            if (asset == nullptr)
                return;

            length = AAsset_getRemainingLength(reinterpret_cast<AAsset*>(asset));
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
            Flush();
            std::fclose(handle);
            handle = nullptr;
        }

        if (asset)
        {
            AAsset_close(reinterpret_cast<AAsset*>(asset));
            asset = nullptr;
        }
    }

    int FileStream::Read(void* buffer, int size)
    {
        if (size <= 0 || canRead == false)
            return 0;

        if (handle)
            return static_cast<int>(std::fread(buffer, 1, size, handle));
        else if (asset)
            return static_cast<int>(AAsset_read(reinterpret_cast<AAsset*>(asset), buffer, size));
        else
            return 0;
    }

    int FileStream::Write(const void* buffer, int size)
    {
        if (handle == nullptr || size <= 0 || canWrite == false)
            return 0;

        return static_cast<int>(std::fwrite(buffer, 1, size, handle));
    }

    void FileStream::Flush()
    {
        if (handle == nullptr || canWrite == false)
            return;

        std::fflush(handle);
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

        if (handle)
            return std::fseek(handle, offset, seekOrigin);
        else if (asset)
            return static_cast<int>(AAsset_seek(reinterpret_cast<AAsset*>(asset), static_cast<int>(offset), seekOrigin));
        else
            return 0;
    }

    int FileStream::GetPosition()
    {
        if (handle)
            return static_cast<int>(std::ftell(handle));
        else if (asset)
            return static_cast<int>(AAsset_seek(reinterpret_cast<AAsset*>(handle), 0, SEEK_CUR));
        else
            return 0;
    }

    int FileStream::GetLength()
    {
        if (length >= 0)
            return length;

        if (handle)
        {
            const int current = static_cast<int>(std::ftell(handle));
            std::fseek(handle, 0, SEEK_END);
            const int length = std::ftell(handle);
            std::fseek(handle, current, SEEK_SET);

            return length;
        }
        else if (asset)
        {
            return static_cast<int>(AAsset_getLength(reinterpret_cast<AAsset*>(handle)));
        }
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

    void FileStream::SetAndroidAssetManager(void* value)
    {
        Assets = reinterpret_cast<AAssetManager*>(value);
    }
}