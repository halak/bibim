namespace Bibim
{
    UIElement* UIElementFactory::Create(AssetStreamReader& reader)
    {
        return Create(reader, nullptr);
    }

    template <typename T> void UIElementFactory::AddEntry()
    {
        AddEntry(T::ClassID, &T::Read);
    }
}