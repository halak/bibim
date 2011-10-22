#pragma once
#ifndef __BIBIM_EVALUABLESEQUENCES_H__
#define __BIBIM_EVALUABLESEQUENCES_H__

#   include <Bibim/FWD.h>
#   include <Bibim/EvaluableSequenceBase.h>
#   include <Bibim/Sequences.h>

    namespace Bibim
    {
        template <typename T, typename TSequence, typename TKeyframe, char a, char b, char c, char d>
        class EvaluableSequenceTemplate : public EvaluableSequenceBase<T>
        {
            BBComponentClass(EvaluableSequenceTemplate, EvaluableSequenceBase<T>, a, b, c, d);
            public:
                EvaluableSequenceTemplate();
                virtual ~EvaluableSequenceTemplate() { }

                TSequence* GetSource() const { return source; }
                void SetSource(TSequence* value) { source = value; }

            protected:
                void UpdateValue();

            protected:
                int timeIndex;
                SharedPointer<TSequence> source;
        };

        typedef EvaluableSequenceTemplate<bool,       BoolSequence,      BoolKeyframe,      'e', 's', 'b', '_'> EvaluableBoolSequence;
        typedef EvaluableSequenceTemplate<short,      ShortSequence,     ShortKeyframe,     'e', 's', 's', '_'> EvaluableShortSequence;
        typedef EvaluableSequenceTemplate<int,        IntSequence,       IntKeyframe,       'e', 's', 'i', '_'> EvaluableIntSequence;
        typedef EvaluableSequenceTemplate<int64,      LongIntSequence,   LongIntKeyframe,   'e', 's', 'l', '_'> EvaluableLongIntSequence;
        typedef EvaluableSequenceTemplate<float,      FloatSequence,     FloatKeyframe,     'e', 's', 'f', '_'> EvaluableFloatSequence;
        typedef EvaluableSequenceTemplate<double,     DoubleSequence,    DoubleKeyframe,    'e', 's', 'd', '_'> EvaluableDoubleSequence;
        typedef EvaluableSequenceTemplate<Point,      PointSequence,     PointKeyframe,     'e', 's', 'p', '_'> EvaluablePointSequence;
        typedef EvaluableSequenceTemplate<Rect,       RectSequence,      RectKeyframe,      'e', 's', 'r', '_'> EvaluableRectSequence;
        typedef EvaluableSequenceTemplate<RectF,      RectFSequence,     RectFKeyframe,     'e', 's', 'R', 'f'> EvaluableRectFSequence;
        typedef EvaluableSequenceTemplate<Vector2,    Vector2Sequence,   Vector2Keyframe,   'e', 's', 'v', '2'> EvaluableVector2Sequence;
        typedef EvaluableSequenceTemplate<Vector3,    Vector3Sequence,   Vector3Keyframe,   'e', 's', 'v', '3'> EvaluableVector3Sequence;
        typedef EvaluableSequenceTemplate<Vector4,    Vector4Sequence,   Vector4Keyframe,   'e', 's', 'v', '4'> EvaluableVector4Sequence;
        typedef EvaluableSequenceTemplate<GameAsset*, GameAssetSequence, GameAssetKeyframe, 'e', 's', 'v', '4'> EvaluableGameAssetSequence;

        typedef SharedPointer<EvaluableBoolSequence>      EvaluableBoolSequencePtr;
        typedef SharedPointer<EvaluableShortSequence>     EvaluableShortSequencePtr;
        typedef SharedPointer<EvaluableIntSequence>       EvaluableIntSequencePtr;
        typedef SharedPointer<EvaluableLongIntSequence>   EvaluableLongIntSequencePtr;
        typedef SharedPointer<EvaluableFloatSequence>     EvaluableFloatSequencePtr;
        typedef SharedPointer<EvaluableDoubleSequence>    EvaluableDoubleSequencePtr;
        typedef SharedPointer<EvaluablePointSequence>     EvaluablePointSequencePtr;
        typedef SharedPointer<EvaluableRectSequence>      EvaluableRectSequencePtr;
        typedef SharedPointer<EvaluableRectFSequence>     EvaluableRectFSequencePtr;
        typedef SharedPointer<EvaluableVector2Sequence>   EvaluableVector2SequencePtr;
        typedef SharedPointer<EvaluableVector3Sequence>   EvaluableVector3SequencePtr;
        typedef SharedPointer<EvaluableVector4Sequence>   EvaluableVector4SequencePtr;
        typedef SharedPointer<EvaluableGameAssetSequence> EvaluableGameAssetSequencePtr;
    }

#   include <Bibim/EvaluableSequences.inl>

#endif