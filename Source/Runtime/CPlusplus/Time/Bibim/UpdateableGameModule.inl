namespace Bibim
{
    bool UpdateableGameModule::Seal(uint timestamp)
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