#pragma once
#ifndef __BIBIM_VECTOR2SEQUENCE_H__
#define __BIBIM_VECTOR2SEQUENCE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Asset.h>
#   include <Bibim/Vector2.h>

    namespace Bibim
    {
        struct Vector2Keyframe
        {
            typedef Vector2 ValueType;

            ValueType Value;
            float Duration;
            float StartTime;

            Vector2Keyframe();
            Vector2Keyframe(ValueType value, float duration);

            static ValueType Interpolate(const Vector2Keyframe& k1, const Vector2Keyframe& k2, float t);
        };

        class Vector2Sequence : public Asset
        {
            public:
                typedef Vector2Keyframe KeyframeType;

            public:
                Vector2Sequence();
                virtual ~Vector2Sequence();

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