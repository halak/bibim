#include <Bibim/UpdateableGameComponent.h>
#include <Bibim/Timeline.h>

namespace Bibim
{
    UpdateableGameComponent::UpdateableGameComponent()
        : timeline(nullptr),
          lastTimestamp(0xFFFFFFFF)
    {
    }

    UpdateableGameComponent::~UpdateableGameComponent()
    {
    }

    void UpdateableGameComponent::SetTimeline(Timeline* value)
    {
        if (timeline != value)
        {
            if (timeline)
                timeline->Remove(this);

            timeline = value;

            if (timeline)
                timeline->Add(this);
        }
    }

    IUpdateable* UpdateableGameComponent::QueryUpdateableInterface()
    {
        return this;
    }
}