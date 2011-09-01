#include <Bibim/PCH.h>
#include <Bibim/UIFunctionTable.h>

namespace Bibim
{
    UIFunctionTable::UIFunctionTable()
    {
    }

    UIFunctionTable::~UIFunctionTable()
    {
    }

    void UIFunctionTable::Add(const String& name, GlobalFunctionType function)
    {
        items[name] = function;
    }

    bool UIFunctionTable::Remove(const String& name)
    {
        NamedFunctionMap::iterator it = items.find(name);
        if (it != items.end())
        {
            items.erase(it);
            return true;
        }
        else
            return false;
    }

    void UIFunctionTable::Clear()
    {
        items.clear();
    }

    UIFunctionTable::FunctionType UIFunctionTable::Find(const String& name) const
    {
        NamedFunctionMap::const_iterator it = items.find(name);
        if (it != items.end())
            return (*it).second;
        else
            return nullptr;
    }
}