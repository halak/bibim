#pragma once
#ifndef __BIBIM_VECTOR3SEQUENCE_H__
#define __BIBIM_VECTOR3SEQUENCE_H__

#   include <Bibim/FWD.h>
#   include <Bibim/Asset.h>
#   include <Bibim/Vector3.h>

    namespace Bibim
    {
        struct Vector3Keyframe
        {
            typedef Vector3 ValueType;

            ValueType Value;
            float Duration;
            float StartTime;

            Vector3Keyframe();
            Vector3Keyframe(ValueType value, float duration);

            static ValueType Interpolate(const Vector3Keyframe& k1, const Vector3Keyframe& k2, float t);
        };

        class Vector3Sequence : public Asset
        {
            public:
                typedef Vector3Keyframe KeyframeType;

            public:
                Vector3Sequence();
                virtual ~Vector3Sequence();

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