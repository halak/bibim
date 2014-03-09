#include <Bibim/Config.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/GLES2.h>
#include <Bibim/Log.h>
#include <Bibim/String.h>

namespace Bibim
{
#   if (defined(BIBIM_PLATFORM_WINDOWS) && defined(BIBIM_COMPILER_MSVC))
#       pragma comment(lib, "libEGL.lib")
#       pragma comment(lib, "libGLESv2.lib")
#   endif

    void GLES2::CheckLastError(const char* op)
    {
        for (GLint error = glGetError(); error; error = glGetError())
        {
            Log::Error("GLES2", String::CFormat("after %s() glError (0x%x)\n", op, error).CStr());
        }
    }
}

#endif