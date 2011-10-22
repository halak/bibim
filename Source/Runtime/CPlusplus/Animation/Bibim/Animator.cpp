#include <Bibim/PCH.h>
#include <Bibim/Animator.h>
#include <Bibim/AnimationTimeline.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    Animator::Animator()
        : timeline(nullptr),
          active(true)
    {
    }

    Animator::~Animator()
    {
    }

    void Animator::SetTimeline(AnimationTimeline* value)
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

    void Animator::SetActive(bool value)
    {
        if (active != value)
        {
            active = value;

            if (timeline)
                timeline->OnActiveChanged(this);
        }
    }

    void Animator::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        active = reader.ReadBool();
        SetTimeline(static_cast<AnimationTimeline*>(reader.ReadModule(AnimationTimeline::ClassID)));
    }

    void Animator::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        active = o->active;
        SetTimeline(o->timeline);
    }
}