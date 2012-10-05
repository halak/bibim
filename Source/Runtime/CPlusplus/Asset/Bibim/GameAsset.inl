namespace Bibim
{
    GameAsset::GameAsset()
        : status(EmptyStatus),
          revision(0)
    {
    }

    GameAsset::GameAsset(Status status)
        : status(status),
          revision(0)
    {
    }

    GameAsset::Status GameAsset::GetStatus() const
    {
        return status;
    }

    int GameAsset::GetRevision() const
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