#include <Bibim/UpdateableObject.h>
#include <Bibim/Timeline.h>

namespace Bibim
{
    UpdateableObject::UpdateableObject()
        : timeline(nullptr),
          lastTimestamp(0xFFFFFFFF)
    {
    }

    UpdateableObject::~UpdateableObject()
    {
    }

    void UpdateableObject::SetTimeline(Timeline* value)
    {
        if (timeline != value)
        {
            if (timeline)
                timeline->Remove(This<IUpdateable>(this));

            timeline = value;

            if (timeline)
                timeline->Add(This<IUpdateable>(this));
        }
    }
}