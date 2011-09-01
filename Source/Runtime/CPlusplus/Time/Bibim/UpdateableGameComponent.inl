namespace Bibim
{
    Timeline* UpdateableGameComponent::GetTimeline() const
    {
        return timeline;
    }

    bool UpdateableGameComponent::Seal(uint timestamp)
    {
        if (lastTimestamp != timestamp)
        {
            lastTimestamp = timestamp;
            return false;
        }
        else
            return true;
    }
}