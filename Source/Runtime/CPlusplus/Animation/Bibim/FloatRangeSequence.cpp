#include <Bibim/PCH.h>
#include <Bibim/FloatRangeSequence.h>
#include <Bibim/Math.h>
#include <Bibim/SequenceTemplate.h>

namespace Bibim
{
    FloatRangeKeyframe::FloatRangeKeyframe()
        : Value(0.0f, 0.0f),
          Duration(0.0f),
          StartTime(0.0f)
    {
    }

    FloatRangeKeyframe::FloatRangeKeyframe(ValueType value, float duration)
        : Value(value),
          Duration(duration),
          StartTime(0.0f)
    {
    }

    FloatRangeKeyframe::ValueType FloatRangeKeyframe::Interpolate(const FloatRangeKeyframe& k1, const FloatRangeKeyframe& k2, float t)
    {
        if (t <= 0.0f)
            return k1.Value;
        if (t >= 1.0f)
            return k2.Value;

        return ValueType(Math::Interpolate(k1.Value.Min, k2.Value.Min, t),
                         Math::Interpolate(k1.Value.Max, k2.Value.Max, t));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    FloatRangeSequence::FloatRangeSequence()
        : s(new SequenceTemplate<KeyframeType>())
    {
    }

    FloatRangeSequence::~FloatRangeSequence()
    {
        delete s;
    }

    void FloatRangeSequence::AddKeyframe(const KeyframeType& item)
    {
        s->AddKeyframe(item);
    }

    void FloatRangeSequence::InsertKeyframe(int index, const KeyframeType& item)
    {
        s->InsertKeyframe(index, item);
    }

    void FloatRangeSequence::InsertKeyframe(float time, const KeyframeType& item)
    {
        s->InsertKeyframe(time, item);
    }

    void FloatRangeSequence::RemoveKeyframe(int index)
    {
        s->RemoveKeyframe(index);
    }

    void FloatRangeSequence::RemoveKeyframe(float time)
    {
        s->RemoveKeyframe(time);
    }

    void FloatRangeSequence::RemoveAllKeyframes()
    {
        s->RemoveAllKeyframes();
    }

    int FloatRangeSequence::GetNumberOfKeyframes()
    {
        return s->GetNumberOfKeyframes();
    }

    const FloatRangeSequence::KeyframeType& FloatRangeSequence::GetKeyframe(int index)
    {
        return s->GetKeyframe(index);
    }

    const FloatRangeSequence::KeyframeType& FloatRangeSequence::GetKeyframe(float time)
    {
        return s->GetKeyframe(time);
    }

    int FloatRangeSequence::GetKeyframeIndex(float time)
    {
        return s->GetKeyframeIndex(time);
    }

    int FloatRangeSequence::GetKeyframeIndex(float time, int startIndex)
    {
        return s->GetKeyframeIndex(time, startIndex);
    }

    void FloatRangeSequence::SetKeyframe(int index, const KeyframeType& item)
    {
        return s->SetKeyframe(index, item);
    }

    float FloatRangeSequence::GetDuration()
    {
        return s->GetDuration();
    }
}