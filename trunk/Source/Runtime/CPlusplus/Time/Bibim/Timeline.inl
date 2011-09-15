namespace Bibim
{
    const Timeline::ItemCollection& Timeline::GetItems() const
    {
        return items;
    }

    float Timeline::GetSpeed() const
    {
        return speed;
    }
}