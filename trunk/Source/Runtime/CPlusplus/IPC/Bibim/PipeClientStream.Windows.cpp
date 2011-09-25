#include <Bibim/PCH.h>
#include <Bibim/PipeClientStream.h>
#include <Bibim/Assert.h>

namespace Bibim
{
    PipeClientStream::PipeClientStream(const String& name, AccessMode accessMode)
        : PipeStream(name, accessMode)
    {
    }

    PipeClientStream::PipeClientStream(const String& serverName, const String& name, AccessMode accessMode)
        : PipeStream(name, accessMode),
          serverName(serverName)
    {
    }

    PipeClientStream::~PipeClientStream()
    {
    }

    void PipeClientStream::Connect()
    {
        if (IsConnected())
            Disconnect();

        HANDLE newHandle = ::CreateFile(GetFullName().CStr(),
                                        GetPlatformAccessMode(),
                                        0x00000000,
                                        nullptr,
                                        OPEN_EXISTING,
                                        0x00000000,
                                        nullptr);
        if (newHandle != INVALID_HANDLE_VALUE)
            SetHandle(newHandle);
    }

    void PipeClientStream::Disconnect()
    {
        BBAssertDebug(IsConnected());

        ::CloseHandle(GetHandle());
        SetHandle(nullptr);
    }

    bool PipeClientStream::IsConnected() const
    {
        return GetHandle() != nullptr;
    }

    String PipeClientStream::GetFullName() const
    {
        String result;
        if (serverName.IsEmpty())
            result = "\\\\.\\pipe\\";
        else
        {
            result = "\\\\";
            result.Append(serverName);
            result.Append("\\pipe\\");
        }

        result.Append(GetName());

        return result;
    }

    DWORD PipeClientStream::GetPlatformAccessMode() const
    {
        switch (GetAccessMode())
        {
            case ReadOnly:
                return GENERIC_READ;
            case WriteOnly:
                return GENERIC_WRITE;
            case ReadAndWrite:
                return GENERIC_READ | GENERIC_WRITE;
            default:
                BBBreak();
                return 0x00000000;
        }
    }
}