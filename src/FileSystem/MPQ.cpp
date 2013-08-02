#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_WINDOWS))

#include <Bibim/MPQ.h>
#include <StormLib.h>

namespace Bibim
{
    MPQ::MPQ(const String& path)
        : handle(nullptr)
    {
        HANDLE internalHandle = NULL;
        if (SFileOpenArchive(path.CStr(), 0, STREAM_FLAG_READ_ONLY, &internalHandle))
            handle = internalHandle;
        else
        {
            DWORD errorCode = ::GetLastError();
            errorCode = errorCode;
        }
    }

    MPQ::~MPQ()
    {
        Close();
    }

    void MPQ::Close()
    {
        if (handle)
        {
            SFileCloseArchive(handle);
            handle = nullptr;
        }
    }

    bool MPQ::Has(const String& path) const
    {
        if (handle)
            return SFileHasFile(handle, path.CStr());
        else
            return false;
    }
}

#endif