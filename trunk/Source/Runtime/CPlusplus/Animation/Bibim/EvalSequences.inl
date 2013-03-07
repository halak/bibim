#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    EvalSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::EvalSequenceTemplate()
        : timeIndex(0)
    {
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    EvalSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>* EvalSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    EvalSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>* EvalSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::Clone(CloningContext& context) const
    {
        This* clone = new This();
        context.Store(this, clone);
        clone->OnCopy(this, context);
        return clone;
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    void EvalSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::UpdateValue()
    {
        if (source == nullptr || source->GetDuration() == 0.0f)
            return;

        const float duration = source->GetDuration();
        const float clippedTime = this->GetLooped() ? Math::Mod(this->time, duration) : Math::Min(this->time, duration);

        timeIndex = source->GetKeyframeIndex(clippedTime, timeIndex);
        if (timeIndex < source->GetNumberOfKeyframes() - 1)
        {
            const TKeyframe& k1 = source->GetKeyframe(timeIndex);
            const TKeyframe& k2 = source->GetKeyframe(timeIndex + 1);
            SetValue(InterpolateKeyframe(k1, k2, (clippedTime - k1.StartTime) / k1.Duration));
        }
        else
            SetValue(source->GetKeyframe(timeIndex).Value);
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    void EvalSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
        timeIndex = 0;
        source = static_cast<TSequence*>(reader.ReadAsset());
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    void EvalSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::OnCopy(const GameComponent* original, CloningContext& context)
    {
        Base::OnCopy(original, context);
        const This* o = static_cast<const This*>(original);
        timeIndex = o->timeIndex;
        source = o->source;
    }
}