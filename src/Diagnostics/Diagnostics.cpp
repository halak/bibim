#include <Bibim/Config.h>
#include <Bibim/Diagnostics.h>
#include <Bibim/Stream.h>

namespace Bibim
{
    StreamPtr Diagnostics::stream;

    void Diagnostics::SetStream(Stream* value)
    {
        stream = value;
    }
}