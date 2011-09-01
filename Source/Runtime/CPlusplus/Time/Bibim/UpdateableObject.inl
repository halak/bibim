namespace Bibim
{
    Timeline* UpdateableObject::GetTimeline() const
    {
        return timeline;
    }

    bool UpdateableObject::Seal(uint timestamp)
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