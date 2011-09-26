#include <Bibim/UIFunctionEventHandler.h>
#include <Bibim/UIFunctionTable.h>

namespace Bibim
{
    UIFunctionEventHandler::UIFunctionEventHandler()
        : table(nullptr),
          functionName(),
          callable(nullptr),
          callableChanged(true)
    {
    }

    UIFunctionEventHandler::UIFunctionEventHandler(const UIFunctionTable* table, const String& functionName)
        : table(table),
          functionName(functionName),
          callable(nullptr),
          callableChanged(true)
    {
    }

    UIFunctionEventHandler::~UIFunctionEventHandler()
    {
    }

    bool UIFunctionEventHandler::Invoke(const UIEventArgs& args)
    {
        if (callableChanged)
        {
            callableChanged = false;

            if (table && functionName.IsEmpty() == false)
                callable = GetTable()->Find(functionName);
        }

        if (callable)
            return (*callable)(args);
        else
            return false;
    }

    void UIFunctionEventHandler::SetTable(const UIFunctionTable* value)
    {
        if (table != value)
        {
            table = value;
            callable = nullptr;
            callableChanged = true;
        }
    }
 
    void UIFunctionEventHandler::SetFunctionName(const String& value)
    {
        if (functionName != value)
        {
            functionName = value;
            callable = nullptr;
            callableChanged = true;
        }
    }

    UIElement* UIFunctionEventHandler::Read(AssetStreamReader& /*reader*/, UIElement* /*existingInstance*/)
    {
        return nullptr;
    }
}