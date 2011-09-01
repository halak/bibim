#include <Bibim/PCH.h>
#include <Bibim/SpriteSequence.h>
#include <Bibim/SequenceTemplate.h>

namespace Bibim
{
    SpriteKeyframe::SpriteKeyframe()
        : Value(),
          Duration(0.0f),
          StartTime(0.0f)
    {
    }

    SpriteKeyframe::SpriteKeyframe(ValueType value, float duration)
        : Value(value),
          Duration(duration),
          StartTime(0.0f)
    {
    }

    SpriteKeyframe::ValueType SpriteKeyframe::Interpolate(const SpriteKeyframe& k1, const SpriteKeyframe& k2, float t)
    {
        if (t <= 0.0f)
            return k1.Value;
        if (t >= 1.0f)
            return k2.Value;

        return k1.Value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    SpriteSequence::SpriteSequence()
        : s(new SequenceTemplate<KeyframeType>())
    {
    }

    SpriteSequence::~SpriteSequence()
    {
        delete s;
    }

    void SpriteSequence::AddKeyframe(const KeyframeType& item)
    {
        s->AddKeyframe(item);
    }

    void SpriteSequence::InsertKeyframe(int index, const KeyframeType& item)
    {
        s->InsertKeyframe(index, item);
    }

    void SpriteSequence::InsertKeyframe(float time, const KeyframeType& item)
    {
        s->InsertKeyframe(time, item);
    }

    void SpriteSequence::RemoveKeyframe(int index)
    {
        s->RemoveKeyframe(index);
    }

    void SpriteSequence::RemoveKeyframe(float time)
    {
        s->RemoveKeyframe(time);
    }

    void SpriteSequence::RemoveAllKeyframes()
    {
        s->RemoveAllKeyframes();
    }

    int SpriteSequence::GetNumberOfKeyframes()
    {
        return s->GetNumberOfKeyframes();
    }

    const SpriteSequence::KeyframeType& SpriteSequence::GetKeyframe(int index)
    {
        return s->GetKeyframe(index);
    }

    const SpriteSequence::KeyframeType& SpriteSequence::GetKeyframe(float time)
    {
        return s->GetKeyframe(time);
    }

    int SpriteSequence::GetKeyframeIndex(float time)
    {
        return s->GetKeyframeIndex(time);
    }

    int SpriteSequence::GetKeyframeIndex(float time, int startIndex)
    {
        return s->GetKeyframeIndex(time, startIndex);
    }

    void SpriteSequence::SetKeyframe(int index, const KeyframeType& item)
    {
        return s->SetKeyframe(index, item);
    }

    float SpriteSequence::GetDuration()
    {
        return s->GetDuration();
    }
}