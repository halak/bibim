#include <Bibim/PCH.h>
#include <Bibim/Script.h>
#include <Bibim/AssetStreamReader.h>

namespace Bibim
{
    Script::Script()
    {
    }

    Script::Script(Buffer& buffer, FunctionTable& functionTable, StringCollection& stringTable, MoveTag)
    {
        this->buffer.swap(buffer);
        this->functionTable.swap(functionTable);
        this->stringTable.swap(stringTable);
        SetStatus(CompletedStatus);
    }

    Script::~Script()
    {
    }

    const Script::Function* Script::Find(const String& name) const
    {
        for (FunctionTable::const_iterator it = functionTable.begin(); it != functionTable.end(); it++)
        {
            if ((*it).Name == name)
                return &(*it);
        }

        return nullptr;
    }

    GameAsset* Script::Create(StreamReader& reader, GameAsset* /*existingInstance*/)
    {
        const int length = reader.ReadInt32();

        Buffer buffer;
        buffer.resize(length);

        reader.Read(&buffer[0], length);
        const int numberOfFunctions = reader.ReadInt32();
        FunctionTable functionTable;
        functionTable.resize(numberOfFunctions);
        for (int i = 0; i < numberOfFunctions; i++)
        {
            Function& item = functionTable[i];
            item.Name = reader.ReadString();
            item.Position = reader.ReadInt32();
            item.ArgumentStackSize = reader.ReadInt32();
            item.ReturnTypes.resize(reader.ReadInt32());
            for (std::vector<ScriptObjectType>::size_type i = 0; i < item.ReturnTypes.size(); i++)
                item.ReturnTypes[i] = static_cast<ScriptObjectType>(reader.ReadInt32());
            item.ParameterTypes.resize(reader.ReadInt32());
            for (std::vector<ScriptObjectType>::size_type i = 0; i < item.ParameterTypes.size(); i++)
                item.ParameterTypes[i] = static_cast<ScriptObjectType>(reader.ReadInt32());
        }

        const int numberOfStrings = reader.ReadInt32();
        StringCollection stringTable;
        stringTable.reserve(numberOfStrings);
        for (int i = 0; i < numberOfStrings; i++)
            stringTable.push_back(reader.ReadString());

        return new Script(buffer, functionTable, stringTable, MoveTag());
    }
}