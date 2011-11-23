namespace Bibim
{
    bool UpdateableGameComponent::Seal(int timestamp)
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