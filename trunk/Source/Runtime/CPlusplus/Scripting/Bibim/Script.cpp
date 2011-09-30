#include <Bibim/PCH.h>
#include <Bibim/Script.h>
#include <Bibim/AssetStreamReader.h>

namespace Bibim
{
    Script::Script()
    {
    }

    Script::Script(const Buffer& buffer, uint entryPoint)
        : buffer(buffer),
          entryPoint(entryPoint)
    {
        SetStatus(CompletedStatus);
    }

    Script::Script(Buffer& buffer, uint entryPoint, MoveTag)
        : entryPoint(entryPoint)
    {
        this->buffer.swap(buffer);
        SetStatus(CompletedStatus);
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
        const uint32 entryPoint = reader.ReadUInt32();

        return new Script(buffer, entryPoint, MoveTag());
    }
}