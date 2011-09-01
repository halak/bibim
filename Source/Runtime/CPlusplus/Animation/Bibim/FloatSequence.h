#pragma once
#ifndef __BIBIM_FLOATSEQUENCE_H__
#define __BIBIM_FLOATSEQUENCE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Asset.h>

    namespace Bibim
    {
        struct FloatKeyframe
        {
            typedef float ValueType;

            ValueType Value;
            float Duration;
            float StartTime;

            FloatKeyframe();
            FloatKeyframe(ValueType value, float duration);

            static ValueType Interpolate(const FloatKeyframe& k1, const FloatKeyframe& k2, float t);
        };

        class FloatSequence : public Asset
        {
            public:
                typedef FloatKeyframe KeyframeType;

            public:
                FloatSequence();
                virtual ~FloatSequence();

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