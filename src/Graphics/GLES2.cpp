#include <Bibim/Config.h>
#include <Bibim/GLES2.h>
#include <Bibim/Log.h>
#include <Bibim/String.h>

namespace Bibim
{
    void GLES2::CheckLastError(const char* op)
    {
        for (GLint error = glGetError(); error; error = glGetError())
        {
            Log::Error("GLES2", String::CFormat("after %s() glError (0x%x)\n", op, error).CStr());
        }
    }
}