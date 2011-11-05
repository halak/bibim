#include <Bibim/ScriptNativeFunctionTable.h>
#include <map>

namespace Bibim
{
    static std::map<int, ScriptNativeFunctionTable::NativeFunction> Functions;

    void ScriptNativeFunctionTable::Add(int id, NativeFunction function)
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

    ScriptNativeFunctionTable::NativeFunction ScriptNativeFunctionTable::Find(int id)
    {
        std::map<int, NativeFunction>::const_iterator it = Functions.find(id);
        if (it != Functions.end())
            return (*it).second;
        else
            return nullptr;
    }
}