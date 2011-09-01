#pragma once
#ifndef __BIBIM_COLORRANGESEQUENCE_H__
#define __BIBIM_COLORRANGESEQUENCE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Asset.h>
#   include <Bibim/Color.h>
#   include <Bibim/Range.h>

    namespace Bibim
    {
        struct ColorRangeKeyframe
        {
            typedef Range<Color> ValueType;

            ValueType Value;
            float Duration;
            float StartTime;

            ColorRangeKeyframe();
            ColorRangeKeyframe(ValueType value, float duration);
        };

        class ColorRangeSequence : public Asset
        {
            public:
                typedef ColorRangeKeyframe KeyframeType;

            public:
                ColorRangeSequence();
                virtual ~ColorRangeSequence();

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