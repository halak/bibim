#include <Bibim/PCH.h>
#include <Bibim/Timeline.h>
#include <Bibim/Exception.h>
#include <Bibim/Math.h>
#include <algorithm>

namespace Bibim
{
    Timeline::Timeline()
        : speed(1.0f),
          lastTimestamp(0)
    {
    }

    Timeline::Timeline(uint32 id)
        : GameComponent(id),
          speed(1.0f),
          lastTimestamp(0)
    {
    }

    Timeline::~Timeline()
    {
    }

    void Timeline::Update(float dt, uint timestamp)
    {
        if (lastTimestamp == timestamp ||
            GetSpeed() == 0.0f ||
            GetStatus() != ActiveStatus)
            return;

        lastTimestamp = timestamp;

        temporaryItems.resize(items.size());
        for (UpdateableCollection::size_type i = 0; i < temporaryItems.size(); i++)
            temporaryItems[i] = items[i].RawPointer;

        dt *= GetSpeed();
        for (UpdateableCollection::iterator it = temporaryItems.begin(); it != temporaryItems.end(); it++)
        {
            (*it)->Update(dt, timestamp);
        }
    }

    void Timeline::Add(IUpdateable* item)
    {
        if (item == nullptr)
            return;

        items.push_back(item);
    }

    void Timeline::Add(IUpdateablePtr item)
    {
        if (item == nullptr)
            return;

        items.push_back(item);
    }

    bool Timeline::Remove(IUpdateable* item)
    {
        if (item == nullptr)
            return false;

        ItemCollection::iterator it = std::find(items.begin(), items.end(), item);
        if (it != items.end())
        {
            items.erase(it);
            return true;
        }
        else
            return false;
    }

    bool Timeline::Remove(IUpdateablePtr item)
    {
        if (item == nullptr)
            return false;

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
        if (index < 0 || static_cast<int>(items.size()) <= index)
            throw OutOfRangeException(nullptr, index, static_cast<int>(items.size()));

        items.erase(items.begin() + index);
    }

    void Timeline::Clear()
    {
        items.clear();
    }

    const Timeline::ItemCollection& Timeline::GetItems() const
    {
        return items;
    }

    float Timeline::GetSpeed() const
    {
        return speed;
    }
    
    void Timeline::SetSpeed(float value)
    {
        speed = Math::Max(value, 0.0f);
    }

    IUpdateable* Timeline::QueryUpdateableInterface()
    {
        return this;
    }
}