namespace Bibim
{
    uint GameAsset::GetRevision() const
    {
        return revision;
    }

    void GameAsset::IncreaseRevision()
    {
        revision++;
    }
}