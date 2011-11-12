#include <Bibim/PCH.h>
#include <Bibim/Timeline.h>
#include <Bibim/Assert.h>
#include <Bibim/IUpdateable.h>
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

    void Timeline::Update(float dt, int timestamp)
    {
        if (GetSpeed() == 0.0f ||
            GetStatus() != ActiveStatus ||
            Seal(timestamp))
            return;

        const int count = static_cast<int>(items.size());
        temporaryItems.resize(count);
        temporaryObjects.resize(count);
        for (int i = 0; i < count; i++)
        {
            temporaryItems[i] = items[i];
            temporaryObjects[i] = objects[i];
        }

        dt *= GetSpeed();
        for (ItemCollection::iterator it = temporaryItems.begin(); it != temporaryItems.end(); it++)
            (*it)->Update(dt, timestamp);
    }

    void Timeline::Add(IUpdateable* item)
    {
        Add(item, nullptr);
    }

    void Timeline::Add(IUpdateable* item, SharedObject* object)
    {
        if (item == nullptr)
            return;

        BBAssertDebug(Contains(item) == false);

        items.push_back(item);
        objects.push_back(object);
    }

    bool Timeline::Remove(IUpdateable* item)
    {
        ItemCollection::iterator it = std::find(items.begin(), items.end(), item);
        if (it != items.end())
        {
            const int index = std::distance(items.begin(), it);
            items.erase(it);
            objects.erase(objects.begin() + index);
            return true;
        }
        else
            return false;
    }

    void Timeline::RemoveAt(int index)
    {
        BBAssert(0 <= index && index < static_cast<int>(items.size()));

        items.erase(items.begin() + index);
        objects.erase(objects.begin() + index);
    }

    void Timeline::Clear()
    {
        items.clear();
        objects.clear();
    }

    bool Timeline::Contains(IUpdateable* item) const
    {
        return std::find(items.begin(), items.end(), item) != items.end();
    }
    
    void Timeline::SetSpeed(float value)
    {
        speed = Math::Max(value, 0.0f);
    }
}