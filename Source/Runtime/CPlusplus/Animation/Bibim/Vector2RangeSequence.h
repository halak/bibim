#pragma once
#ifndef __BIBIM_VECTOR2RANGESEQUENCE_H__
#define __BIBIM_VECTOR2RANGESEQUENCE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Asset.h>
#   include <Bibim/Range.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        struct Vector2RangeKeyframe
        {
            typedef Range<Vector2> ValueType;

            ValueType Value;
            float Duration;
            float StartTime;

            Vector2RangeKeyframe();
            Vector2RangeKeyframe(ValueType value, float duration);
        };

        class Vector2RangeSequence : public Asset
        {
            public:
                typedef Vector2RangeKeyframe KeyframeType;

            public:
                Vector2RangeSequence ();
                virtual ~Vector2RangeSequence ();

                void AddKeyframe(const KeyframeType& item);
                void InsertKeyframe(int index, const KeyframeType& item);
                void InsertKeyframe(float time, const KeyframeType& item);
                void RemoveKeyframe(int index);
                void RemoveKeyframe(float time);
                void RemoveAllKeyframes();

                int GetNumberOfKeyframes();
                const KeyframeType& GetKeyframe(int index);
                const KeyframeType& GetKeyframe(float time);
                int GetKeyframeIndex(float time);
                int GetKeyframeIndex(float time, int startIndex);
                void SetKeyframe(int index, const KeyframeType& item);

                float GetDuration();
           
            private:
                SequenceTemplate<KeyframeType>* s;
        };
    }

#endif