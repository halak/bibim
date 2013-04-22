#include <Bibim/Config.h>
#include <Bibim/TimelineGameModule.h>
#include <Bibim/Timeline.h>

namespace Bibim
{
    TimelineGameModule::TimelineGameModule()
        : timeline(nullptr)
    {
    }

    TimelineGameModule::~TimelineGameModule()
    {
        if (timeline)
            timeline->Remove(this);
    }

    void TimelineGameModule::SetTimeline(Timeline* value)
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
}