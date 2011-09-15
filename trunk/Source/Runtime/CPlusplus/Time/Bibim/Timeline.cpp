#include <Bibim/PCH.h>
#include <Bibim/Timeline.h>
#include <Bibim/Assert.h>
#include <Bibim/Math.h>
#include <algorithm>

namespace Bibim
{
    Timeline::Timeline()
        : speed(1.0f)
    {
    }

    Timeline::~Timeline()
    {
    }

    void Timeline::Update(float dt, uint timestamp)
    {
        if (GetSpeed() == 0.0f ||
            GetStatus() != ActiveStatus ||
            Seal(timestamp))
            return;

        temporaryItems.resize(items.size());
        for (ItemCollection::size_type i = 0; i < temporaryItems.size(); i++)
            temporaryItems[i] = items[i];

        dt *= GetSpeed();
        for (ItemCollection::iterator it = temporaryItems.begin(); it != temporaryItems.end(); it++)
        {
            (*it)->Update(dt, timestamp);
        }
    }

    void Timeline::Add(UpdateableGameModule* item)
    {
        if (item == nullptr)
            return;

        BBAssertDebug(Contains(item) == false);

        items.push_back(item);
    }

    bool Timeline::Remove(UpdateableGameModule* item)
    {
        ItemCollection::iterator it = std::find(items.begin(), items.end(), item);
        if (it != items.end())
        {
            items.erase(it);
            return true;
        }
        else
            return false;
    }

    void Timeline::RemoveAt(int index)
    {
        BBAssert(0 <= index && index < static_cast<int>(items.size()));

        items.erase(items.begin() + index);
    }

    void Timeline::Clear()
    {
        items.clear();
    }

    bool Timeline::Contains(UpdateableGameModule* item) const
    {
        return std::find(items.begin(), items.end(), item) != items.end();
    }
    
    void Timeline::SetSpeed(float value)
    {
        speed = Math::Max(value, 0.0f);
    }
}