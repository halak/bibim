#include <Bibim/PCH.h>
#include <Bibim/FloatSequence.h>
#include <Bibim/Math.h>
#include <Bibim/SequenceTemplate.h>

namespace Bibim
{
    FloatKeyframe::FloatKeyframe()
        : Value(0.0f),
          Duration(0.0f),
          StartTime(0.0f)
    {
    }

    FloatKeyframe::FloatKeyframe(ValueType value, float duration)
        : Value(value),
          Duration(duration),
          StartTime(0.0f)
    {
    }

    FloatKeyframe::ValueType FloatKeyframe::Interpolate(const FloatKeyframe& k1, const FloatKeyframe& k2, float t)
    {
        if (t <= 0.0f)
            return k1.Value;
        if (t >= 1.0f)
            return k2.Value;

        return Math::Interpolate(k1.Value, k2.Value, t);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    FloatSequence::FloatSequence()
        : s(new SequenceTemplate<KeyframeType>())
    {
    }

    FloatSequence::~FloatSequence()
    {
        delete s;
    }

    void FloatSequence::AddKeyframe(const KeyframeType& item)
    {
        s->AddKeyframe(item);
    }

    void FloatSequence::InsertKeyframe(int index, const KeyframeType& item)
    {
        s->InsertKeyframe(index, item);
    }

    void FloatSequence::InsertKeyframe(float time, const KeyframeType& item)
    {
        s->InsertKeyframe(time, item);
    }

    void FloatSequence::RemoveKeyframe(int index)
    {
        s->RemoveKeyframe(index);
    }

    void FloatSequence::RemoveKeyframe(float time)
    {
        s->RemoveKeyframe(time);
    }

    void FloatSequence::RemoveAllKeyframes()
    {
        s->RemoveAllKeyframes();
    }

    int FloatSequence::GetNumberOfKeyframes()
    {
        return s->GetNumberOfKeyframes();
    }

    const FloatSequence::KeyframeType& FloatSequence::GetKeyframe(int index)
    {
        return s->GetKeyframe(index);
    }

    const FloatSequence::KeyframeType& FloatSequence::GetKeyframe(float time)
    {
        return s->GetKeyframe(time);
    }

    int FloatSequence::GetKeyframeIndex(float time)
    {
        return s->GetKeyframeIndex(time);
    }

    int FloatSequence::GetKeyframeIndex(float time, int startIndex)
    {
        return s->GetKeyframeIndex(time, startIndex);
    }

    void FloatSequence::SetKeyframe(int index, const KeyframeType& item)
    {
        return s->SetKeyframe(index, item);
    }

    float FloatSequence::GetDuration()
    {
        return s->GetDuration();
    }
}