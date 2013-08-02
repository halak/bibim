#pragma once
#ifndef __BIBIM_EVALUABLERANGEDSEQUENCES_H__
#define __BIBIM_EVALUABLERANGEDSEQUENCES_H__

#include <Bibim/FWD.h>
#include <Bibim/EvalSequenceBase.h>
#include <Bibim/Sequences.h>
#include <Bibim/ComponentStreamReader.h>

namespace Bibim
{
    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    class EvalRangedSequenceTemplate : public EvalSequenceBase<T>
    {
        BBComponentClass(EvalRangedSequenceTemplate, EvalSequenceBase<T>, a, b, c, d);
        public:
            EvalRangedSequenceTemplate();
            virtual ~EvalRangedSequenceTemplate() { }

            TSequence* GetSource1() const { return source1; }
            void SetSource1(TSequence* value) { source1 = value; }

            TSequence* GetSource2() const { return source2; }
            void SetSource2(TSequence* value) { source2 = value; }

        protected:
            void UpdateValue();

        protected:
            int timeIndex1;
            int timeIndex2;
            SharedPointer<TSequence> source1;
            SharedPointer<TSequence> source2;
    };

    typedef EvalRangedSequenceTemplate<bool,       BoolSequence,      BoolKeyframe,      'e', 'r', 'b', '_'> EvalBoolRangedSequence;
    typedef EvalRangedSequenceTemplate<short,      ShortIntSequence,  ShortIntKeyframe,  'e', 'r', 's', '_'> EvalShortIntRangedSequence;
    typedef EvalRangedSequenceTemplate<int,        IntSequence,       IntKeyframe,       'e', 'r', 'i', '_'> EvalIntRangedSequence;
    typedef EvalRangedSequenceTemplate<longint,    LongIntSequence,   LongIntKeyframe,   'e', 'r', 'l', '_'> EvalLongIntRangedSequence;
    typedef EvalRangedSequenceTemplate<float,      FloatSequence,     FloatKeyframe,     'e', 'r', 'f', '_'> EvalFloatRangedSequence;
    typedef EvalRangedSequenceTemplate<double,     DoubleSequence,    DoubleKeyframe,    'e', 'r', 'd', '_'> EvalDoubleRangedSequence;
    typedef EvalRangedSequenceTemplate<Color,      ColorSequence,     ColorKeyframe,     'e', 'r', 'c', '_'> EvalColorRangedSequence;
    typedef EvalRangedSequenceTemplate<Point2,     Point2Sequence,    Point2Keyframe,    'e', 'r', 'p', '2'> EvalPoint2RangedSequence;
    typedef EvalRangedSequenceTemplate<Point3,     Point3Sequence,    Point3Keyframe,    'e', 'r', 'p', '3'> EvalPoint3RangedSequence;
    typedef EvalRangedSequenceTemplate<Point4,     Point4Sequence,    Point4Keyframe,    'e', 'r', 'p', '4'> EvalPoint4RangedSequence;
    typedef EvalRangedSequenceTemplate<Rect,       RectSequence,      RectKeyframe,      'e', 'r', 'r', '_'> EvalRectRangedSequence;
    typedef EvalRangedSequenceTemplate<RectF,      RectFSequence,     RectFKeyframe,     'e', 'r', 'R', 'f'> EvalRectFRangedSequence;
    typedef EvalRangedSequenceTemplate<Vector2,    Vector2Sequence,   Vector2Keyframe,   'e', 'r', 'v', '2'> EvalVector2RangedSequence;
    typedef EvalRangedSequenceTemplate<Vector3,    Vector3Sequence,   Vector3Keyframe,   'e', 'r', 'v', '3'> EvalVector3RangedSequence;
    typedef EvalRangedSequenceTemplate<Vector4,    Vector4Sequence,   Vector4Keyframe,   'e', 'r', 'v', '4'> EvalVector4RangedSequence;
    typedef EvalRangedSequenceTemplate<GameAsset*, GameAssetSequence, GameAssetKeyframe, 'e', 'r', 'a', '_'> EvalGameAssetRangedSequence;

    typedef SharedPointer<EvalBoolRangedSequence>      EvalBoolRangedSequencePtr;
    typedef SharedPointer<EvalShortIntRangedSequence>  EvalShortIntRangedSequencePtr;
    typedef SharedPointer<EvalIntRangedSequence>       EvalIntRangedSequencePtr;
    typedef SharedPointer<EvalLongIntRangedSequence>   EvalLongIntRangedSequencePtr;
    typedef SharedPointer<EvalFloatRangedSequence>     EvalFloatRangedSequencePtr;
    typedef SharedPointer<EvalDoubleRangedSequence>    EvalDoubleRangedSequencePtr;
    typedef SharedPointer<EvalColorRangedSequence>     EvalColorRangedSequencePtr;
    typedef SharedPointer<EvalPoint2RangedSequence>    EvalPoint2RangedSequencePtr;
    typedef SharedPointer<EvalPoint3RangedSequence>    EvalPoint3RangedSequencePtr;
    typedef SharedPointer<EvalPoint4RangedSequence>    EvalPoint4RangedSequencePtr;
    typedef SharedPointer<EvalRectRangedSequence>      EvalRectRangedSequencePtr;
    typedef SharedPointer<EvalRectFRangedSequence>     EvalRectFRangedSequencePtr;
    typedef SharedPointer<EvalVector2RangedSequence>   EvalVector2RangedSequencePtr;
    typedef SharedPointer<EvalVector3RangedSequence>   EvalVector3RangedSequencePtr;
    typedef SharedPointer<EvalVector4RangedSequence>   EvalVector4RangedSequencePtr;
    typedef SharedPointer<EvalGameAssetRangedSequence> EvalGameAssetRangedSequencePtr;

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::EvalRangedSequenceTemplate()
        : timeIndex1(0),
          timeIndex2(0)
    {
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>* EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::Clone() const
    {
        CloningContext context;
        return Clone(context);
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>* EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::Clone(CloningContext& context) const
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

        const float clippedTime1 = this->GetLooped() ? Math::Mod(this->time, duration1) : Math::Min(this->time, duration1);
        const float clippedTime2 = this->GetLooped() ? Math::Mod(this->time, duration2) : Math::Min(this->time, duration2);

        timeIndex1 = source1->GetKeyframeIndex(clippedTime1, timeIndex1);
        timeIndex2 = source2->GetKeyframeIndex(clippedTime2, timeIndex2);

        if (timeIndex1 < source1->GetNumberOfKeyframes() - 1)
        {
            const TKeyframe& k1 = source1->GetKeyframe(timeIndex1);
            const TKeyframe& k2 = source1->GetKeyframe(timeIndex1 + 1);
            this->SetValue(InterpolateKeyframe(k1, k2, (clippedTime1 - k1.StartTime) / k1.Duration));
        }
        else
            this->SetValue(source1->GetKeyframe(timeIndex1).Value);
    }

    template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
    void EvalRangedSequenceTemplate<T, TSequence, TKeyframe, a, b, c, d>::OnRead(ComponentStreamReader& reader)
    {
        Base::OnRead(reader);
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

#endif