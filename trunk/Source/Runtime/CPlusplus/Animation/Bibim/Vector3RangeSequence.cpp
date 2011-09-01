#include <Bibim/PCH.h>
#include <Bibim/Vector3RangeSequence.h>
#include <Bibim/SequenceTemplate.h>

namespace Bibim
{
    Vector3RangeKeyframe::Vector3RangeKeyframe()
        : Value(Vector3::Zero, Vector3::Zero),
          Duration(0.0f),
          StartTime(0.0f)
    {
    }

    Vector3RangeKeyframe::Vector3RangeKeyframe(ValueType value, float duration)
        : Value(value),
          Duration(duration),
          StartTime(0.0f)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector3RangeSequence::Vector3RangeSequence()
        : s(new SequenceTemplate<KeyframeType>())
    {
    }

    Vector3RangeSequence::~Vector3RangeSequence()
    {
        delete s;
    }

    void Vector3RangeSequence::AddKeyframe(const KeyframeType& item)
    {
        s->AddKeyframe(item);
    }

    void Vector3RangeSequence::InsertKeyframe(int index, const KeyframeType& item)
    {
        s->InsertKeyframe(index, item);
    }

    void Vector3RangeSequence::InsertKeyframe(float time, const KeyframeType& item)
    {
        s->InsertKeyframe(time, item);
    }

    void Vector3RangeSequence::RemoveKeyframe(int index)
    {
        s->RemoveKeyframe(index);
    }

    void Vector3RangeSequence::RemoveKeyframe(float time)
    {
        s->RemoveKeyframe(time);
    }

    void Vector3RangeSequence::RemoveAllKeyframes()
    {
        s->RemoveAllKeyframes();
    }

    int Vector3RangeSequence::GetNumberOfKeyframes()
    {
        return s->GetNumberOfKeyframes();
    }

    const Vector3RangeSequence::KeyframeType& Vector3RangeSequence::GetKeyframe(int index)
    {
        return s->GetKeyframe(index);
    }

    const Vector3RangeSequence::KeyframeType& Vector3RangeSequence::GetKeyframe(float time)
    {
        return s->GetKeyframe(time);
    }

    int Vector3RangeSequence::GetKeyframeIndex(float time)
    {
        return s->GetKeyframeIndex(time);
    }

    int Vector3RangeSequence::GetKeyframeIndex(float time, int startIndex)
    {
        return s->GetKeyframeIndex(time, startIndex);
    }

    void Vector3RangeSequence::SetKeyframe(int index, const KeyframeType& item)
    {
        return s->SetKeyframe(index, item);
    }

    float Vector3RangeSequence::GetDuration()
    {
        return s->GetDuration();
    }
}