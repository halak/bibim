#include <Bibim/Config.h>
#include <Bibim/Performance.h>
#include <Bibim/Stream.h>

namespace Bibim
{
    StreamPtr Performance::stream;

    void Performance::SetStream(Stream* value)
    {
        stream = value;
    }
}