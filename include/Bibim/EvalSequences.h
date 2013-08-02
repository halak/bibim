#pragma once
#ifndef __BIBIM_EVALUABLESEQUENCES_H__
#define __BIBIM_EVALUABLESEQUENCES_H__

#include <Bibim/FWD.h>
#include <Bibim/EvalSequenceBase.h>
#include <Bibim/ComponentStreamReader.h>
#include <Bibim/Sequences.h>

namespace Bibim
{
    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    class EvalSequenceTemplate : public EvalSequenceBase<T>
    {
        BBComponentClass(EvalSequenceTemplate, EvalSequenceBase<T>, a, b, c, d);
        public:
            EvalSequenceTemplate();
            virtual ~EvalSequenceTemplate() { }

            TSequence* GetSource() const { return source; }
            void SetSource(TSequence* value) { source = value; }

        protected:
            void UpdateValue();

        protected:
            int timeIndex;
            SharedPointer<TSequence> source;
    };

    typedef EvalSequenceTemplate<bool,       BoolSequence,      BoolKeyframe,      'e', 's', 'b', '_'> EvalBoolSequence;
    typedef EvalSequenceTemplate<short,      ShortIntSequence,  ShortIntKeyframe,  'e', 's', 's', '_'> EvalShortIntSequence;
    typedef EvalSequenceTemplate<int,        IntSequence,       IntKeyframe,       'e', 's', 'i', '_'> EvalIntSequence;
    typedef EvalSequenceTemplate<longint,    LongIntSequence,   LongIntKeyframe,   'e', 's', 'l', '_'> EvalLongIntSequence;
    typedef EvalSequenceTemplate<float,      FloatSequence,     FloatKeyframe,     'e', 's', 'f', '_'> EvalFloatSequence;
    typedef EvalSequenceTemplate<double,     DoubleSequence,    DoubleKeyframe,    'e', 's', 'd', '_'> EvalDoubleSequence;
    typedef EvalSequenceTemplate<Color,      ColorSequence,     ColorKeyframe,     'e', 's', 'c', '_'> EvalColorSequence;
    typedef EvalSequenceTemplate<Point2,     Point2Sequence,    Point2Keyframe,    'e', 's', 'p', '2'> EvalPoint2Sequence;
    typedef EvalSequenceTemplate<Point3,     Point3Sequence,    Point3Keyframe,    'e', 's', 'p', '3'> EvalPoint3Sequence;
    typedef EvalSequenceTemplate<Point4,     Point4Sequence,    Point4Keyframe,    'e', 's', 'p', '4'> EvalPoint4Sequence;
    typedef EvalSequenceTemplate<Rect,       RectSequence,      RectKeyframe,      'e', 's', 'r', '_'> EvalRectSequence;
    typedef EvalSequenceTemplate<RectF,      RectFSequence,     RectFKeyframe,     'e', 's', 'R', 'f'> EvalRectFSequence;
    typedef EvalSequenceTemplate<Vector2,    Vector2Sequence,   Vector2Keyframe,   'e', 's', 'v', '2'> EvalVector2Sequence;
    typedef EvalSequenceTemplate<Vector3,    Vector3Sequence,   Vector3Keyframe,   'e', 's', 'v', '3'> EvalVector3Sequence;
    typedef EvalSequenceTemplate<Vector4,    Vector4Sequence,   Vector4Keyframe,   'e', 's', 'v', '4'> EvalVector4Sequence;
    typedef EvalSequenceTemplate<GameAsset*, GameAssetSequence, GameAssetKeyframe, 'e', 's', 'a', '_'> EvalGameAssetSequence;

    typedef SharedPointer<EvalBoolSequence>      EvalBoolSequencePtr;
    typedef SharedPointer<EvalShortIntSequence>  EvalShortIntSequencePtr;
    typedef SharedPointer<EvalIntSequence>       EvalIntSequencePtr;
    typedef SharedPointer<EvalLongIntSequence>   EvalLongIntSequencePtr;
    typedef SharedPointer<EvalFloatSequence>     EvalFloatSequencePtr;
    typedef SharedPointer<EvalDoubleSequence>    EvalDoubleSequencePtr;
    typedef SharedPointer<EvalColorSequence>     EvalColorSequencePtr;
    typedef SharedPointer<EvalPoint2Sequence>    EvalPoint2SequencePtr;
    typedef SharedPointer<EvalPoint3Sequence>    EvalPoint3SequencePtr;
    typedef SharedPointer<EvalPoint4Sequence>    EvalPoint4SequencePtr;
    typedef SharedPointer<EvalRectSequence>      EvalRectSequencePtr;
    typedef SharedPointer<EvalRectFSequence>     EvalRectFSequencePtr;
    typedef SharedPointer<EvalVector2Sequence>   EvalVector2SequencePtr;
    typedef SharedPointer<EvalVector3Sequence>   EvalVector3SequencePtr;
    typedef SharedPointer<EvalVector4Sequence>   EvalVector4SequencePtr;
    typedef SharedPointer<EvalGameAssetSequence> EvalGameAssetSequencePtr;

    ////////////////////////////////////////////////////////////////////////////////////////////////////

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
            this->SetValue(InterpolateKeyframe(k1, k2, (clippedTime - k1.StartTime) / k1.Duration));
        }
        else
            this->SetValue(source->GetKeyframe(timeIndex).Value);
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

#endif