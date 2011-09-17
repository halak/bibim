namespace Bibim
{
    GameAsset::Status GameAsset::GetStatus() const
    {
        return status;
    }

    uint GameAsset::GetRevision() const
    {
        return revision;
    }

    void GameAsset::SetStatus(Status value)
    {
        status = value;
    }

    void GameAsset::IncreaseRevision()
    {
        revision++;
    }
}