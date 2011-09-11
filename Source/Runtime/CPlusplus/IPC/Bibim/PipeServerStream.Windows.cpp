#include <Bibim/PCH.h>
#include <Bibim/PipeServerStream.h>

namespace Bibim
{
    PipeServerStream::PipeServerStream(const String& name, AccessMode accessMode)
    {
    }

    PipeServerStream::~PipeServerStream()
    {
    }

    //void PipeServerStream::Initialize()
    //{
    //    DWORD win32OpenMode = 0x00000000;
    //    switch (GetOpenMode())
    //    {
    //        case ReadOnly:
    //            break;
    //        case WriteOnly:
    //            break;
    //        case ReadAndWrite:
    //            break;
    //    }

    //    SetHandle(::CreateNamedPipe(GetFullName().CStr(),
    //                                win32OpenMode,
    //                                PIPE_TYPE_BYTE,
    //                                PIPE_UNLIMITED_INSTANCES,
    //                                4096, 4096,
    //                                0,
    //                                NULL));
    //}
}