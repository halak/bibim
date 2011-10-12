namespace Bibim
{
    GameAsset* GameAssetFactory::Create(StreamReader& reader)
    {
        return Create(reader, nullptr);
    }

    template <typename T> void GameAssetFactory::AddEntry()
    {
        AddEntry(T::ClassID, &T::Create);
    }
}