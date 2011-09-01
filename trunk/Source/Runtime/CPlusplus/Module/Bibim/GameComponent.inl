namespace Bibim
{
    uint32 GameComponent::GetID() const
    {
        return id;
    }

    GameComponent::Status GameComponent::GetStatus() const
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

    bool GameComponent::GetAlive() const
    {
        return alive;
    }

    bool GameComponent::GetActive() const
    {
        return active;
    }
}