#include <Bibim/PCH.h>
#include <Bibim/UIStreamReader.h>

namespace Bibim
{
    UIStreamReader::UIStreamReader(Stream* sourceStream)
        : BinaryReader(sourceStream)
    {
    }

    UIStreamReader::~UIStreamReader()
    {
    }
}