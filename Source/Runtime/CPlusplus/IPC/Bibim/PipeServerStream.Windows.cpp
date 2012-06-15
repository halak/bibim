#include <Bibim/PCH.h>
#include <Bibim/PipeServerStream.h>

namespace Bibim
{
    PipeServerStream::PipeServerStream(const String& name, AccessMode accessMode)
        : PipeStream(name, accessMode)
    {
        String fullName = "\\\\.\\pipe\\";
        fullName.Append(name);

        DWORD win32AccessMode = 0x00000000;
        switch (GetAccessMode())
        {
            case ReadOnly:
                win32AccessMode = PIPE_ACCESS_INBOUND;
                break;
            case WriteOnly:
                win32AccessMode = PIPE_ACCESS_OUTBOUND;
                break;
            case ReadAndWrite:
                win32AccessMode = PIPE_ACCESS_DUPLEX;
                break;
        }

        HANDLE newHandle = ::CreateNamedPipe(fullName.CStr(),
                                             win32AccessMode,
                                             PIPE_TYPE_BYTE,
                                             PIPE_UNLIMITED_INSTANCES,
                                             4096,
                                             4096,
                                             0,
                                             nullptr);
        if (newHandle != INVALID_HANDLE_VALUE)
            SetHandle(newHandle);
    }

    PipeServerStream::~PipeServerStream()
    {
        if (GetHandle() != nullptr)
        {
            HANDLE handle = GetHandle();
            ::CloseHandle(handle);
            SetHandle(nullptr);
        }
    }

    bool PipeServerStream::WaitForConnection()
    {
        BOOL connected = ::ConnectNamedPipe(GetHandle(), nullptr);
        if (connected == FALSE && GetLastError() == ERROR_PIPE_CONNECTED)
            connected = TRUE;

        return (connected == TRUE) ? true : false;
    }

    void PipeServerStream::Disconnect()
    {
        BBAssertDebug(GetHandle() != nullptr);

        HANDLE handle = GetHandle();
        ::FlushFileBuffers(handle);
        ::DisconnectNamedPipe(handle);
    }

    bool PipeServerStream::IsConnected() const
    {
        if (GetHandle() != nullptr)
        {
            ULONG id = 0;
            if (::GetNamedPipeClientProcessId(GetHandle(), &id))
                return id != 0;
            else
                return false;
        }
        else
            return false;
    }
}