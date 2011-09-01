#include <Bibim/PCH.h>
#include <Bibim/Vector3Sequence.h>
#include <Bibim/Math.h>
#include <Bibim/SequenceTemplate.h>

namespace Bibim
{
    Vector3Keyframe::Vector3Keyframe()
        : Value(Vector3::Zero),
          Duration(0.0f),
          StartTime(0.0f)
    {
    }

    Vector3Keyframe::Vector3Keyframe(ValueType value, float duration)
        : Value(value),
          Duration(duration),
          StartTime(0.0f)
    {
    }

    Vector3Keyframe::ValueType Vector3Keyframe::Interpolate(const Vector3Keyframe& k1, const Vector3Keyframe& k2, float t)
    {
        if (t <= 0.0f)
            return k1.Value;
        if (t >= 1.0f)
            return k2.Value;

        return Math::Interpolate(k1.Value, k2.Value, t);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector3Sequence::Vector3Sequence()
        : s(new SequenceTemplate<KeyframeType>())
    {
    }

    Vector3Sequence::~Vector3Sequence()
    {
        delete s;
    }

    void Vector3Sequence::AddKeyframe(const KeyframeType& item)
    {
        s->AddKeyframe(item);
    }

    void Vector3Sequence::InsertKeyframe(int index, const KeyframeType& item)
    {
        s->InsertKeyframe(index, item);
    }

    void Vector3Sequence::InsertKeyframe(float time, const KeyframeType& item)
    {
        s->InsertKeyframe(time, item);
    }

    void Vector3Sequence::RemoveKeyframe(int index)
    {
        s->RemoveKeyframe(index);
    }

    void Vector3Sequence::RemoveKeyframe(float time)
    {
        s->RemoveKeyframe(time);
    }

    void Vector3Sequence::RemoveAllKeyframes()
    {
        s->RemoveAllKeyframes();
    }

    int Vector3Sequence::GetNumberOfKeyframes()
    {
        return s->GetNumberOfKeyframes();
    }

    const Vector3Sequence::KeyframeType& Vector3Sequence::GetKeyframe(int index)
    {
        return s->GetKeyframe(index);
    }

    const Vector3Sequence::KeyframeType& Vector3Sequence::GetKeyframe(float time)
    {
        return s->GetKeyframe(time);
    }

    int Vector3Sequence::GetKeyframeIndex(float time)
    {
        return s->GetKeyframeIndex(time);
    }

    int Vector3Sequence::GetKeyframeIndex(float time, int startIndex)
    {
        return s->GetKeyframeIndex(time, startIndex);
    }

    void Vector3Sequence::SetKeyframe(int index, const KeyframeType& item)
    {
        return s->SetKeyframe(index, item);
    }

    float Vector3Sequence::GetDuration()
    {
        return s->GetDuration();
    }
}