namespace Bibim
{
    UIElement* UIElementFactory::Create(StreamReader& reader)
    {
        return Create(reader, nullptr);
    }

    template <typename T> void UIElementFactory::AddEntry()
    {
        AddEntry(T::ClassID, &T::Create);
    }
}