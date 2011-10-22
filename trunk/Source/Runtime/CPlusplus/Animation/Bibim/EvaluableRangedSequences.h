#pragma once
#ifndef __BIBIM_EVALUABLERANGEDSEQUENCES_H__
#define __BIBIM_EVALUABLERANGEDSEQUENCES_H__

#   include <Bibim/FWD.h>
#   include <Bibim/EvaluableSequenceBase.h>
#   include <Bibim/Sequences.h>

    namespace Bibim
    {
        template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
        class EvaluableRangedSequenceTemplate : public EvaluableSequenceBase<T>
        {
            BBComponentClass(EvaluableRangedSequenceTemplate, EvaluableSequenceBase<T>, a, b, c, d);
            public:
                EvaluableRangedSequenceTemplate();
                virtual ~EvaluableRangedSequenceTemplate() { }

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

        typedef EvaluableRangedSequenceTemplate<bool,       BoolSequence,      BoolKeyframe,      'e', 's', 'b', '_'> EvaluableBoolRangedSequence;
        typedef EvaluableRangedSequenceTemplate<short,      ShortSequence,     ShortKeyframe,     'e', 's', 's', '_'> EvaluableShortRangedSequence;
        typedef EvaluableRangedSequenceTemplate<int,        IntSequence,       IntKeyframe,       'e', 's', 'i', '_'> EvaluableIntRangedSequence;
        typedef EvaluableRangedSequenceTemplate<int64,      LongIntSequence,   LongIntKeyframe,   'e', 's', 'l', '_'> EvaluableLongIntRangedSequence;
        typedef EvaluableRangedSequenceTemplate<float,      FloatSequence,     FloatKeyframe,     'e', 's', 'f', '_'> EvaluableFloatRangedSequence;
        typedef EvaluableRangedSequenceTemplate<double,     DoubleSequence,    DoubleKeyframe,    'e', 's', 'd', '_'> EvaluableDoubleRangedSequence;
        typedef EvaluableRangedSequenceTemplate<Point,      PointSequence,     PointKeyframe,     'e', 's', 'p', '_'> EvaluablePointRangedSequence;
        typedef EvaluableRangedSequenceTemplate<Rect,       RectSequence,      RectKeyframe,      'e', 's', 'r', '_'> EvaluableRectRangedSequence;
        typedef EvaluableRangedSequenceTemplate<RectF,      RectFSequence,     RectFKeyframe,     'e', 's', 'R', 'f'> EvaluableRectFRangedSequence;
        typedef EvaluableRangedSequenceTemplate<Vector2,    Vector2Sequence,   Vector2Keyframe,   'e', 's', 'v', '2'> EvaluableVector2RangedSequence;
        typedef EvaluableRangedSequenceTemplate<Vector3,    Vector3Sequence,   Vector3Keyframe,   'e', 's', 'v', '3'> EvaluableVector3RangedSequence;
        typedef EvaluableRangedSequenceTemplate<Vector4,    Vector4Sequence,   Vector4Keyframe,   'e', 's', 'v', '4'> EvaluableVector4RangedSequence;
        typedef EvaluableRangedSequenceTemplate<GameAsset*, GameAssetSequence, GameAssetKeyframe, 'e', 's', 'v', '4'> EvaluableGameAssetRangedSequence;

        typedef SharedPointer<EvaluableBoolRangedSequence>      EvaluableBoolRangedSequencePtr;
        typedef SharedPointer<EvaluableShortRangedSequence>     EvaluableShortRangedSequencePtr;
        typedef SharedPointer<EvaluableIntRangedSequence>       EvaluableIntRangedSequencePtr;
        typedef SharedPointer<EvaluableLongIntRangedSequence>   EvaluableLongIntRangedSequencePtr;
        typedef SharedPointer<EvaluableFloatRangedSequence>     EvaluableFloatRangedSequencePtr;
        typedef SharedPointer<EvaluableDoubleRangedSequence>    EvaluableDoubleRangedSequencePtr;
        typedef SharedPointer<EvaluablePointRangedSequence>     EvaluablePointRangedSequencePtr;
        typedef SharedPointer<EvaluableRectRangedSequence>      EvaluableRectRangedSequencePtr;
        typedef SharedPointer<EvaluableRectFRangedSequence>     EvaluableRectFRangedSequencePtr;
        typedef SharedPointer<EvaluableVector2RangedSequence>   EvaluableVector2RangedSequencePtr;
        typedef SharedPointer<EvaluableVector3RangedSequence>   EvaluableVector3RangedSequencePtr;
        typedef SharedPointer<EvaluableVector4RangedSequence>   EvaluableVector4RangedSequencePtr;
        typedef SharedPointer<EvaluableGameAssetRangedSequence> EvaluableGameAssetRangedSequencePtr;
    }

#   include <Bibim/EvaluableRangedSequences.inl>

#endif