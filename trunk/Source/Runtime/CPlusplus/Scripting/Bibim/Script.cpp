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
        const int length = reader.ReadInt();

        Buffer buffer;
        buffer.resize(length);

        reader.Read(&buffer[0], length);
        const int numberOfFunctions = reader.ReadInt();
        FunctionTable functionTable;
        functionTable.resize(numberOfFunctions);
        for (int i = 0; i < numberOfFunctions; i++)
        {
            Function& item = functionTable[i];
            item.Name = reader.ReadString();
            item.Position = reader.ReadInt();
            item.ArgumentStackSize = reader.ReadInt();
            item.ReturnTypes.resize(reader.ReadInt());
            for (std::vector<AnyType>::size_type i = 0; i < item.ReturnTypes.size(); i++)
                item.ReturnTypes[i] = static_cast<AnyType>(reader.ReadInt());
            item.ParameterTypes.resize(reader.ReadInt());
            for (std::vector<AnyType>::size_type i = 0; i < item.ParameterTypes.size(); i++)
                item.ParameterTypes[i] = static_cast<AnyType>(reader.ReadInt());
        }

        const int numberOfStrings = reader.ReadInt();
        StringCollection stringTable;
        stringTable.reserve(numberOfStrings);
        for (int i = 0; i < numberOfStrings; i++)
            stringTable.push_back(reader.ReadString());

        return new Script(buffer, functionTable, stringTable, MoveTag());
    }
}