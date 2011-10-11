#include <Bibim/ScriptNativeFunctionTable.h>
#include <map>

namespace Bibim
{
    static std::map<uint32, ScriptNativeFunctionTable::NativeFunction> Functions;

    void ScriptNativeFunctionTable::Add(uint32 id, NativeFunction function)
    {
        Functions[id] = function;
    }

    void ScriptNativeFunctionTable::Add(Entry item)
    {
        Functions[item.ID] = item.Function;
    }

    void ScriptNativeFunctionTable::AddRange(const Entry* items, int count)
    {
        for (int i = 0; i < count; i++)
            Functions[items[i].ID] = items[i].Function;
    }

    ScriptNativeFunctionTable::NativeFunction ScriptNativeFunctionTable::Find(uint32 id)
    {
        std::map<uint32, NativeFunction>::const_iterator it = Functions.find(id);
        if (it != Functions.end())
            return (*it).second;
        else
            return nullptr;
    }
}