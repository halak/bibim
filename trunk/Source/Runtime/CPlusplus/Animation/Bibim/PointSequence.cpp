#include <Bibim/PCH.h>
#include <Bibim/PointSequence.h>
#include <Bibim/Math.h>
#include <Bibim/SequenceTemplate.h>

namespace Bibim
{
    PointKeyframe::PointKeyframe()
        : Value(Point::Zero),
          Duration(0.0f),
          StartTime(0.0f)
    {
    }

    PointKeyframe::PointKeyframe(ValueType value, float duration)
        : Value(value),
          Duration(duration),
          StartTime(0.0f)
    {
    }

    PointKeyframe::ValueType PointKeyframe::Interpolate(const PointKeyframe& k1, const PointKeyframe& k2, float t)
    {
        if (t <= 0.0f)
            return k1.Value;
        if (t >= 1.0f)
            return k2.Value;

        return Math::Interpolate(k1.Value, k2.Value, t);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    PointSequence::PointSequence()
        : s(new SequenceTemplate<KeyframeType>())
    {
    }

    PointSequence::~PointSequence()
    {
        delete s;
    }

    void PointSequence::AddKeyframe(const KeyframeType& item)
    {
        s->AddKeyframe(item);
    }

    void PointSequence::InsertKeyframe(int index, const KeyframeType& item)
    {
        s->InsertKeyframe(index, item);
    }

    void PointSequence::InsertKeyframe(float time, const KeyframeType& item)
    {
        s->InsertKeyframe(time, item);
    }

    void PointSequence::RemoveKeyframe(int index)
    {
        s->RemoveKeyframe(index);
    }

    void PointSequence::RemoveKeyframe(float time)
    {
        s->RemoveKeyframe(time);
    }

    void PointSequence::RemoveAllKeyframes()
    {
        s->RemoveAllKeyframes();
    }

    int PointSequence::GetNumberOfKeyframes()
    {
        return s->GetNumberOfKeyframes();
    }

    const PointSequence::KeyframeType& PointSequence::GetKeyframe(int index)
    {
        return s->GetKeyframe(index);
    }

    const PointSequence::KeyframeType& PointSequence::GetKeyframe(float time)
    {
        return s->GetKeyframe(time);
    }

    int PointSequence::GetKeyframeIndex(float time)
    {
        return s->GetKeyframeIndex(time);
    }

    int PointSequence::GetKeyframeIndex(float time, int startIndex)
    {
        return s->GetKeyframeIndex(time, startIndex);
    }

    void PointSequence::SetKeyframe(int index, const KeyframeType& item)
    {
        return s->SetKeyframe(index, item);
    }

    float PointSequence::GetDuration()
    {
        return s->GetDuration();
    }
}