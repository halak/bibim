#include <Bibim/Math.h>

namespace Bibim
{
    template <typename T> EvaluableSequenceTemplate<T>::EvaluableSequenceTemplate()
        : time(0.0f),
          timeIndex(0),
          velocity(1.0f),
          looped(false),
          timeChanged(true),
          source(),
          value(),
          lastTimestamp(0)
    {
    }
    
    template <typename T> EvaluableSequenceTemplate<T>::~EvaluableSequenceTemplate()
    {
    }

    template <typename T> void EvaluableSequenceTemplate<T>::Update(float dt, uint timestamp)
    {
        if (lastTimestamp == timestamp)
            return;
        else
            lastTimestamp = timestamp;

        time += dt;
        timeChanged = true;
    }

    template <typename T> typename EvaluableSequenceTemplate<T>::ValueType EvaluableSequenceTemplate<T>::Evaluate()
    {
        if (timeChanged)
        {
            timeChanged = false;
            UpdateValue();
        }

        return value;
    }

    template <typename T> float EvaluableSequenceTemplate<T>::GetTime() const
    {
        return time;
    }

    template <typename T> float EvaluableSequenceTemplate<T>::GetVelocity() const
    {
        return velocity;
    }

    template <typename T> void EvaluableSequenceTemplate<T>::SetVelocity(float value)
    {
        velocity = value;
    }

    template <typename T> bool EvaluableSequenceTemplate<T>::GetLooped() const
    {
        return looped;
    }

    template <typename T> void EvaluableSequenceTemplate<T>::SetLooped(bool value)
    {
        looped = value;
    }

    template <typename T> T EvaluableSequenceTemplate<T>::GetSource() const
    {
        return source;
    }

    template <typename T> void EvaluableSequenceTemplate<T>::SetSource(T value)
    {
        source = value;
    }

    template <typename T> void EvaluableSequenceTemplate<T>::UpdateValue()
    {
        if (source == nullptr || source->GetDuration() == 0.0f)
            return;

        const float duration = source->GetDuration();
        const float clippedTime = GetLooped() ? Math::Mod(time, duration) : Math::Min(time, duration);

        timeIndex = source->GetKeyframeIndex(clippedTime, timeIndex);
        if (timeIndex < source->GetNumberOfKeyframes() - 1)
        {
            const KeyframeType& k1 = source->GetKeyframe(timeIndex);
            const KeyframeType& k2 = source->GetKeyframe(timeIndex + 1);
            value = KeyframeType::Interpolate(k1, k2, (clippedTime - k1.StartTime) / k1.Duration);
        }
        else
            value = source->GetKeyframe(timeIndex).Value;
    }
}