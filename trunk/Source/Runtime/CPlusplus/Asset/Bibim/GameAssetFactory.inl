namespace Bibim
{
    GameAsset* GameAssetFactory::Create(AssetReader& reader)
    {
        return Create(reader, nullptr);
    }

    template <typename T> void GameAssetFactory::AddEntry()
    {
        AddEntry(T::ClassID, &T::Read);
    }
}