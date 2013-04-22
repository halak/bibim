#include <Bibim/Config.h>
#include <Bibim/MPQ.h>
#include <StormLib.h>

namespace Bibim
{
    MPQ::MPQ(const String& path)
        : handle(INVALID_HANDLE_VALUE)
    {
        HANDLE win32Handle = NULL;
        if (SFileOpenArchive(path.CStr(), 0, STREAM_FLAG_READ_ONLY, &win32Handle))
            handle = win32Handle;
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
        if (handle != INVALID_HANDLE_VALUE)
        {
            SFileCloseArchive(handle);
            handle = INVALID_HANDLE_VALUE;
        }
    }

    bool MPQ::Has(const String& path) const
    {
        if (handle != INVALID_HANDLE_VALUE)
            return SFileHasFile(handle, path.CStr());
        else
            return false;
    }
}