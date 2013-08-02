#include <Bibim/UIFunctionEventHandler.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/UIFunctionTable.h>

namespace Bibim
{
    BBImplementsComponent(UIFunctionEventHandler);

    UIFunctionEventHandler::UIFunctionEventHandler()
        : table(nullptr),
          functionName(),
          callable(UIFunctionTable::FunctionType(nullptr, nullptr)),
          callableChanged(true)
    {
    }

    UIFunctionEventHandler::UIFunctionEventHandler(const UIFunctionTable* table, const String& functionName)
        : table(table),
          functionName(functionName),
          callable(UIFunctionTable::FunctionType(nullptr, nullptr)),
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

        if (callable.first)
            return (*(callable.first))(args, callable.second);
        else
            return false;
    }

    void UIFunctionEventHandler::SetTable(const UIFunctionTable* value)
    {
        if (table != value)
        {
            table = value;
            callable.first  = nullptr;
            callable.second = nullptr;
            callableChanged = true;
        }
    }
 
    void UIFunctionEventHandler::SetFunctionName(const String& value)
    {
        if (functionName != value)
        {
            functionName = value;
            callable.first  = nullptr;
            callable.second = nullptr;
            callableChanged = true;
        }
    }

    void UIFunctionEventHandler::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        table = static_cast<UIFunctionTable*>(reader.ReadModule());
        functionName = reader.ReadString();
        callableChanged = true;
    }

    void UIFunctionEventHandler::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const UIFunctionEventHandler* o = static_cast<const UIFunctionEventHandler*>(original);
        table = o->table;
        functionName = o->functionName;
        callable = o->callable;
        callableChanged = o->callableChanged;
    }
}