namespace Bibim
{
    AnimationTimeline* Animator::GetTimeline() const
    {
        return timeline;
    }

    bool Animator::GetActive() const
    {
        return active;
    }
}