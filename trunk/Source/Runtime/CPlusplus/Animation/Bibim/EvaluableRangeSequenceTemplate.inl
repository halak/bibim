/**
namespace Bibim
{
    template <typename T> EvaluableRangeSequenceTemplate<T>::EvaluableRangeSequenceTemplate()
        : EvaluableSequenceTemplate<T>()
    {
    }

    template <typename T> EvaluableRangeSequenceTemplate<T>::EvaluableRangeSequenceTemplate(ulong seed)
        : EvaluableSequenceTemplate<T>(),
          randomEngine(seed)
    {
    }

    template <typename T> EvaluableRangeSequenceTemplate<T>::~EvaluableRangeSequenceTemplate()
    {
    }

    template <typename T> typename EvaluableRangeSequenceTemplate<T>::ValueType::ElementType EvaluableRangeSequenceTemplate<T>::Evaluate()
    {
        if (timeChanged)
        {
            timeChanged = false;
            UpdateValue();
        }

        return value;
    }

    template <typename T> void EvaluableRangeSequenceTemplate<T>::SetSeed(ulong seed)
    {
        randomEngine.seed(seed);
    }

    template <typename T> void EvaluableRangeSequenceTemplate<T>::UpdateValue()
    {
        if (source == nullptr || source->GetDuration() == 0.0f)
            return;

        const float duration = source->GetDuration();
        const float clippedTime = GetLooped() ? Math::Mod(time, duration) : Math::Min(time, duration);

        const int oldTimeIndex = timeIndex;
        const int newTimeIndex = source->GetKeyframeIndex(clippedTime, oldTimeIndex);

        //if (newTimeIndex < source->GetNumberOfKeyframes() - 1)
        //{
        //    const KeyframeType& k1 = source->GetKeyframe(timeIndex);
        //    const KeyframeType& k2 = source->GetKeyframe(timeIndex + 1);
        //    value = KeyframeType::Interpolate(k1, k2, (clippedTime - k1.StartTime) / k1.Duration);
        //}
        //else
        //    value = source->GetKeyframe(timeIndex).Value;

        timeIndex = newTimeIndex;
    }
}
**/