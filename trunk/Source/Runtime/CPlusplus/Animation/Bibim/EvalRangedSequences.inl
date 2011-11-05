#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::EvalRangedSequenceTemplate()
        : timeIndex1(0),
          timeIndex2(0)
    {
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>* EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::Clone(CloningContext& /*context*/) const
    {
        This* clone = new This();
        context.Store(this, clone);
        clone->OnCopy(this, context);
        return clone;
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    void EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::UpdateValue()
    {
        if (source1 == nullptr || source2 == nullptr)
            return;

        const float duration1 = source1->GetDuration();
        if (duration1 == 0.0f)
            return;

        const float duration2 = source2->GetDuration();
        if (duration2 == 0.0f)
            return;

        const float clippedTime1 = GetLooped() ? Math::Mod(time, duration1) : Math::Min(time, duration1);
        const float clippedTime2 = GetLooped() ? Math::Mod(time, duration2) : Math::Min(time, duration2);

        timeIndex1 = source1->GetKeyframeIndex(clippedTime1, timeIndex1);
        timeIndex2 = source2->GetKeyframeIndex(clippedTime2, timeIndex2);

        if (timeIndex1 < source1->GetNumberOfKeyframes() - 1)
        {
            const TKeyframe& k1 = source1->GetKeyframe(timeIndex1);
            const TKeyframe& k2 = source1->GetKeyframe(timeIndex1 + 1);
            SetValue(InterpolateKeyframe(k1, k2, (clippedTime1 - k1.StartTime) / k1.Duration));
        }
        else
            SetValue(source1->GetKeyframe(timeIndex1).Value);
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    void EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::onRead(reader);
        timeIndex1 = 0;
        timeIndex2 = 0;
        source1 = static_cast<TSequence*>(reader.ReadAsset());
        source2 = static_cast<TSequence*>(reader.ReadAsset());
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    void EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        timeIndex1 = o->timeIndex1;
        timeIndex2 = o->timeIndex2;
        source1 = o->source1;
        source2 = o->source2;
    }
}