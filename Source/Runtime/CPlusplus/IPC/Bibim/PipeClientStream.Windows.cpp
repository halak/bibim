#include <Bibim/PCH.h>
#include <Bibim/PipeClientStream.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    PipeClientStream::PipeClientStream()
    {
    }

    PipeClientStream::PipeClientStream(const String& name, AccessMode accessMode)
    {
        Open(name, accessMode);
    }

    PipeClientStream::PipeClientStream(const String& machineName, const String& name, AccessMode accessMode)
    {
        Open(machineName, name, accessMode);
    }

    PipeClientStream::~PipeClientStream()
    {
        if (IsOpen())
            Close();
    }

    bool PipeClientStream::Open(const String& name, AccessMode accessMode)
    {
        if (IsOpen())
            Close();

        String fullName = "\\\\.\\pipe\\";
        fullName.Append(name);
        return OpenActually(fullName, name, accessMode);
    }

    bool PipeClientStream::Open(const String& machineName, const String& name, AccessMode accessMode)
    {
        if (IsOpen())
            Close();

        if (machineName.IsEmpty() == false)
        {
            String fullName = "\\\\";
            fullName.Append(machineName);
            fullName.Append("\\pipe\\");
            fullName.Append(name);
            return OpenActually(fullName, name, accessMode);
        }
        else
            return Open(name, accessMode);
    }

    void PipeClientStream::Close()
    {
        BBAssertDebug(IsOpen());
        PipeStream::Finalize();
    }

    bool PipeClientStream::OpenActually(const String& fullName, const String& name, AccessMode accessMode)
    {
        DWORD win32AccessMode = 0x00000000;
        switch (accessMode)
        {
            case ReadOnly:
                win32AccessMode = GENERIC_READ;
                break;
            case WriteOnly:
                win32AccessMode = GENERIC_WRITE;
                break;
            case ReadAndWrite:
                win32AccessMode = GENERIC_READ | GENERIC_WRITE;
                break;
        }

        HANDLE handle = ::CreateFile(fullName.CStr(), win32AccessMode, 0x00000000, NULL, OPEN_EXISTING, 0x00000000, NULL);
        if (handle != INVALID_HANDLE_VALUE)
        {
            PipeStream::Initialize(handle, name, accessMode);
            return true;
        }
        else
        {
            PipeStream::Initialize(INVALID_HANDLE_VALUE, String::Empty, ReadOnly);
            return false;
        }
    }
}