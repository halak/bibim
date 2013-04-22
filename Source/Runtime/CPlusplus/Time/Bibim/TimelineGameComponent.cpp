#include <Bibim/Config.h>
#include <Bibim/TimelineGameComponent.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Timeline.h>

namespace Bibim
{
    TimelineGameComponent::TimelineGameComponent()
        : timeline(nullptr)
    {
    }

    TimelineGameComponent::~TimelineGameComponent()
    {
        if (timeline)
            timeline->Remove(this);
    }

    void TimelineGameComponent::SetTimeline(Timeline* value)
    {
        if (timeline != value)
        {
            if (timeline)
                timeline->Remove(this);

            timeline = value;

            if (timeline)
                timeline->Add(this, this);
        }
    }

    void TimelineGameComponent::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        SetTimeline(static_cast<Timeline*>(reader.ReadModule(Timeline::ClassID)));
    }
    
    void TimelineGameComponent::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        SetTimeline(o->timeline);
    }
}