#include <Bibim/PCH.h>
#include <Bibim/Vector2RangeSequence.h>
#include <Bibim/SequenceTemplate.h>

namespace Bibim
{
    Vector2RangeKeyframe::Vector2RangeKeyframe()
        : Value(Vector2::Zero, Vector2::Zero),
          Duration(0.0f),
          StartTime(0.0f)
    {
    }

    Vector2RangeKeyframe::Vector2RangeKeyframe(ValueType value, float duration)
        : Value(value),
          Duration(duration),
          StartTime(0.0f)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2RangeSequence::Vector2RangeSequence()
        : s(new SequenceTemplate<KeyframeType>())
    {
    }

    Vector2RangeSequence::~Vector2RangeSequence()
    {
        delete s;
    }

    void Vector2RangeSequence::AddKeyframe(const KeyframeType& item)
    {
        s->AddKeyframe(item);
    }

    void Vector2RangeSequence::InsertKeyframe(int index, const KeyframeType& item)
    {
        s->InsertKeyframe(index, item);
    }

    void Vector2RangeSequence::InsertKeyframe(float time, const KeyframeType& item)
    {
        s->InsertKeyframe(time, item);
    }

    void Vector2RangeSequence::RemoveKeyframe(int index)
    {
        s->RemoveKeyframe(index);
    }

    void Vector2RangeSequence::RemoveKeyframe(float time)
    {
        s->RemoveKeyframe(time);
    }

    void Vector2RangeSequence::RemoveAllKeyframes()
    {
        s->RemoveAllKeyframes();
    }

    int Vector2RangeSequence::GetNumberOfKeyframes()
    {
        return s->GetNumberOfKeyframes();
    }

    const Vector2RangeSequence::KeyframeType& Vector2RangeSequence::GetKeyframe(int index)
    {
        return s->GetKeyframe(index);
    }

    const Vector2RangeSequence::KeyframeType& Vector2RangeSequence::GetKeyframe(float time)
    {
        return s->GetKeyframe(time);
    }

    int Vector2RangeSequence::GetKeyframeIndex(float time)
    {
        return s->GetKeyframeIndex(time);
    }

    int Vector2RangeSequence::GetKeyframeIndex(float time, int startIndex)
    {
        return s->GetKeyframeIndex(time, startIndex);
    }

    void Vector2RangeSequence::SetKeyframe(int index, const KeyframeType& item)
    {
        return s->SetKeyframe(index, item);
    }

    float Vector2RangeSequence::GetDuration()
    {
        return s->GetDuration();
    }
}