#include <Bibim/PCH.h>
#include <Bibim/SubTimeline.h>

namespace Bibim
{
    SubTimeline::SubTimeline()
        : parent(nullptr)
    {
    }

    SubTimeline::SubTimeline(uint32 id)
        : Timeline(id),
          parent(nullptr)
    {
    }

    SubTimeline::~SubTimeline()
    {
    }

    void SubTimeline::SetParent(Timeline* value)
    {
        if (parent != value)
        {
            Timeline* oldParent = parent;

            if (oldParent)
                oldParent->Remove(this);

            parent = value;

            if (parent)
                parent->Add(this);
        }
    }
}