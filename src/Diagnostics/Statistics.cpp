#include <Bibim/Config.h>
#include <Bibim/Statistics.h>
#include <Bibim/Stream.h>

namespace Bibim
{
    StreamPtr Statistics::stream;

    void Statistics::SetStream(Stream* value)
    {
        stream = value;
    }
}