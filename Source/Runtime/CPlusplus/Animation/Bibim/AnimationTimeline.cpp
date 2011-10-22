#include <Bibim/PCH.h>
#include <Bibim/AnimationTimeline.h>
#include <Bibim/Animator.h>
#include <Bibim/Assert.h>
#include <algorithm>

namespace Bibim
{
    AnimationTimeline::AnimationTimeline()
    {
    }

    AnimationTimeline::~AnimationTimeline()
    {
    }

    void AnimationTimeline::Add(Animator* item)
    {
        BBAssertDebug(item != nullptr);

        AnimatorPtr sharedItem = item;

        BBAssertDebug(std::find(animators.begin(), animators.end(), item) == animators.end());

        animators.push_back(item);

        if (item->GetActive())
            activeAnimators.push_back(item);
    }

    void AnimationTimeline::Remove(Animator* item)
    {
        BBAssertDebug(item != nullptr);

        AnimatorPtr sharedItem = item;

        AnimatorCollection::iterator it = std::find(animators.begin(), animators.end(), item);
        BBAssertDebug(it != animators.end());

        animators.erase(it);

        if (item->GetActive())
        {
            it = std::find(activeAnimators.begin(), activeAnimators.end(), item);
            BBAssertDebug(it != activeAnimators.end());

            activeAnimators.erase(it);
        }
    }

    void AnimationTimeline::OnActiveChanged(Animator* item)
    {
        BBAssertDebug(item != nullptr);
        BBAssertDebug(std::find(animators.begin(), animators.end(), item) != animators.end());

        AnimatorPtr sharedItem = item;

        if (item->GetActive())
        {
            BBAssertDebug(std::find(activeAnimators.begin(), activeAnimators.end(), item) == activeAnimators.end());
            activeAnimators.push_back(item);
        }
        else
        {
            AnimatorCollection::iterator it = std::find(activeAnimators.begin(), activeAnimators.end(), item);
            BBAssertDebug(it != activeAnimators.end());
            activeAnimators.erase(it);
        }
    }
}