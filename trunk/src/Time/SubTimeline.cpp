#include <Bibim/Config.h>
#include <Bibim/SubTimeline.h>

namespace Bibim
{
    SubTimeline::SubTimeline()
        : parent(nullptr)
    {
    }

    SubTimeline::~SubTimeline()
    {
        if (parent)
            parent->Remove(this);
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