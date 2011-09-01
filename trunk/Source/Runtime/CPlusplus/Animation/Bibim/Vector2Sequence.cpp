#include <Bibim/PCH.h>
#include <Bibim/Vector2Sequence.h>
#include <Bibim/Math.h>
#include <Bibim/SequenceTemplate.h>

namespace Bibim
{
    Vector2Keyframe::Vector2Keyframe()
        : Value(Vector2::Zero),
          Duration(0.0f),
          StartTime(0.0f)
    {
    }

    Vector2Keyframe::Vector2Keyframe(ValueType value, float duration)
        : Value(value),
          Duration(duration),
          StartTime(0.0f)
    {
    }

    Vector2Keyframe::ValueType Vector2Keyframe::Interpolate(const Vector2Keyframe& k1, const Vector2Keyframe& k2, float t)
    {
        if (t <= 0.0f)
            return k1.Value;
        if (t >= 1.0f)
            return k2.Value;

        return Math::Interpolate(k1.Value, k2.Value, t);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2Sequence::Vector2Sequence()
        : s(new SequenceTemplate<KeyframeType>())
    {
    }

    Vector2Sequence::~Vector2Sequence()
    {
        delete s;
    }

    void Vector2Sequence::AddKeyframe(const KeyframeType& item)
    {
        s->AddKeyframe(item);
    }

    void Vector2Sequence::InsertKeyframe(int index, const KeyframeType& item)
    {
        s->InsertKeyframe(index, item);
    }

    void Vector2Sequence::InsertKeyframe(float time, const KeyframeType& item)
    {
        s->InsertKeyframe(time, item);
    }

    void Vector2Sequence::RemoveKeyframe(int index)
    {
        s->RemoveKeyframe(index);
    }

    void Vector2Sequence::RemoveKeyframe(float time)
    {
        s->RemoveKeyframe(time);
    }

    void Vector2Sequence::RemoveAllKeyframes()
    {
        s->RemoveAllKeyframes();
    }

    int Vector2Sequence::GetNumberOfKeyframes()
    {
        return s->GetNumberOfKeyframes();
    }

    const Vector2Sequence::KeyframeType& Vector2Sequence::GetKeyframe(int index)
    {
        return s->GetKeyframe(index);
    }

    const Vector2Sequence::KeyframeType& Vector2Sequence::GetKeyframe(float time)
    {
        return s->GetKeyframe(time);
    }

    int Vector2Sequence::GetKeyframeIndex(float time)
    {
        return s->GetKeyframeIndex(time);
    }

    int Vector2Sequence::GetKeyframeIndex(float time, int startIndex)
    {
        return s->GetKeyframeIndex(time, startIndex);
    }

    void Vector2Sequence::SetKeyframe(int index, const KeyframeType& item)
    {
        return s->SetKeyframe(index, item);
    }

    float Vector2Sequence::GetDuration()
    {
        return s->GetDuration();
    }
}