namespace Bibim
{
    uint32 GameModule::GetID() const
    {
        return id;
    }

    GameModule::Status GameModule::GetStatus() const
    {
        if (alive)
        {
            if (active)
                return ActiveStatus;
            else
                return AliveStatus;
        }
        else
            return DeadStatus;
    }

    bool GameModule::GetAlive() const
    {
        return alive;
    }

    bool GameModule::GetActive() const
    {
        return active;
    }
}