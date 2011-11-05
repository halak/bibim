namespace Bibim
{
    bool UpdateableGameModule::Seal(int timestamp)
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