namespace Bibim
{
    const UIFunctionTable* UIFunctionEventHandler::GetTable() const
    {
        return table;
    }

    const String& UIFunctionEventHandler::GetFunctionName() const
    {
        return functionName;
    }
}