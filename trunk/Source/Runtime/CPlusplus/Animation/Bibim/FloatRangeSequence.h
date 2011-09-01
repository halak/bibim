#pragma once
#ifndef __BIBIM_FLOATRANGESEQUENCE_H__
#define __BIBIM_FLOATRANGESEQUENCE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Asset.h>
#   include <Bibim/Range.h>

    namespace Bibim
    {
        struct FloatRangeKeyframe
        {
            typedef Range<float> ValueType;

            ValueType Value;
            float Duration;
            float StartTime;

            FloatRangeKeyframe();
            FloatRangeKeyframe(ValueType value, float duration);

            static ValueType Interpolate(const FloatRangeKeyframe& k1, const FloatRangeKeyframe& k2, float t);
        };

        class FloatRangeSequence : public Asset
        {
            public:
                typedef FloatRangeKeyframe KeyframeType;

            public:
                FloatRangeSequence();
                virtual ~FloatRangeSequence();

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