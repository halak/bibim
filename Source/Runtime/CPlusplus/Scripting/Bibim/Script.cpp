#include <Bibim/PCH.h>
#include <Bibim/Script.h>
#include <Bibim/AssetStreamReader.h>

namespace Bibim
{
    Script::Script()
    {
    }

    Script::Script(const Buffer& buffer)
        : buffer(buffer)
    {
    }

    Script::Script(Buffer& buffer, MoveTag)
    {
        this->buffer.swap(buffer);
    }

    Script::~Script()
    {
    }

    GameAsset* Script::Read(AssetStreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const int length = reader.ReadInt32();

        Buffer buffer;
        buffer.resize(length);

        reader.Read(&buffer[0], length);

        return new Script(buffer, MoveTag());
    }
}