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

    Script::Script(Buffer& buffer, uint entryPoint, StringCollection& stringTable, MoveTag)
        : entryPoint(entryPoint)
    {
        this->buffer.swap(buffer);
        this->stringTable.swap(stringTable);
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

        const int numberOfStrings = reader.ReadInt32();
        StringCollection stringTable;
        stringTable.reserve(numberOfStrings);
        for (int i = 0; i < numberOfStrings; i++)
            stringTable.push_back(reader.ReadString());

        return new Script(buffer, entryPoint, stringTable, MoveTag());
    }
}