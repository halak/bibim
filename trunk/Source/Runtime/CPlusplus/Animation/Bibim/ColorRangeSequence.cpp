#include <Bibim/PCH.h>
#include <Bibim/ColorRangeSequence.h>
#include <Bibim/SequenceTemplate.h>

namespace Bibim
{
    ColorRangeKeyframe::ColorRangeKeyframe()
        : Value(Color(255, 255, 255, 255), Color(255, 255, 255, 255)),
          Duration(0.0f),
          StartTime(0.0f)
    {
    }

    ColorRangeKeyframe::ColorRangeKeyframe(ValueType value, float duration)
        : Value(value),
          Duration(duration),
          StartTime(0.0f)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ColorRangeSequence::ColorRangeSequence()
        : s(new SequenceTemplate<KeyframeType>())
    {
    }

    ColorRangeSequence::~ColorRangeSequence()
    {
        delete s;
    }

    void ColorRangeSequence::AddKeyframe(const KeyframeType& item)
    {
        s->AddKeyframe(item);
    }

    void ColorRangeSequence::InsertKeyframe(int index, const KeyframeType& item)
    {
        s->InsertKeyframe(index, item);
    }

    void ColorRangeSequence::InsertKeyframe(float time, const KeyframeType& item)
    {
        s->InsertKeyframe(time, item);
    }

    void ColorRangeSequence::RemoveKeyframe(int index)
    {
        s->RemoveKeyframe(index);
    }

    void ColorRangeSequence::RemoveKeyframe(float time)
    {
        s->RemoveKeyframe(time);
    }

    void ColorRangeSequence::RemoveAllKeyframes()
    {
        s->RemoveAllKeyframes();
    }

    int ColorRangeSequence::GetNumberOfKeyframes()
    {
        return s->GetNumberOfKeyframes();
    }

    const ColorRangeSequence::KeyframeType& ColorRangeSequence::GetKeyframe(int index)
    {
        return s->GetKeyframe(index);
    }

    const ColorRangeSequence::KeyframeType& ColorRangeSequence::GetKeyframe(float time)
    {
        return s->GetKeyframe(time);
    }

    int ColorRangeSequence::GetKeyframeIndex(float time)
    {
        return s->GetKeyframeIndex(time);
    }

    int ColorRangeSequence::GetKeyframeIndex(float time, int startIndex)
    {
        return s->GetKeyframeIndex(time, startIndex);
    }

    void ColorRangeSequence::SetKeyframe(int index, const KeyframeType& item)
    {
        return s->SetKeyframe(index, item);
    }

    float ColorRangeSequence::GetDuration()
    {
        return s->GetDuration();
    }
}