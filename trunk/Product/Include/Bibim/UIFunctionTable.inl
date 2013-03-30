namespace Bibim
{
    void UIFunctionTable::Add(const String& name, GlobalFunctionType function)
    {
        Add(name, function, nullptr);
    }
}