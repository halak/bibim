#pragma once
#ifndef __BIBIM_SEQUENCES_H__
#define __BIBIM_SEQUENCES_H__

#include <Bibim/FWD.h>
#include <Bibim/GameAsset.h>
#include <Bibim/Math.h>
#include <vector>

namespace Bibim
{
    template <typename T> struct Keyframe
    {
        T Value;
        float Duration;
        float StartTime;

        Keyframe();
        Keyframe(T value, float duration);
    };

    template <typename T, char a, char b, char c, char d> class SequenceTemplate : public GameAsset
    {
        BBSerializableAssetClass(SequenceTemplate, GameAsset, a, b, c, d);
        public:
            SequenceTemplate();
            virtual ~SequenceTemplate();

            void AddKeyframe(const Keyframe<T>& item);
            void InsertKeyframe(int index, const Keyframe<T>& item);
            void InsertKeyframe(float time, const Keyframe<T>& item);
            void RemoveKeyframe(int index);
            void RemoveKeyframe(float time);
            void RemoveAllKeyframes();

            int GetNumberOfKeyframes() const;
            const Keyframe<T>& GetKeyframe(int index);
            const Keyframe<T>& GetKeyframe(float time);
            int GetKeyframeIndex(float time, int startIndex = 0);
            void SetKeyframe(int index, const Keyframe<T>& item);

            float GetDuration();

        private:
            void ResetDuration();
            void UpdateStartTimes();

        private:
            std::vector<Keyframe<T> > keyframes;
            float duration;
            bool startTimeChanged;
    };

    typedef Keyframe<bool>         BoolKeyframe;
    typedef Keyframe<short>        ShortIntKeyframe;
    typedef Keyframe<int>          IntKeyframe;
    typedef Keyframe<longint>      LongIntKeyframe;
    typedef Keyframe<float>        FloatKeyframe;
    typedef Keyframe<double>       DoubleKeyframe;
    typedef Keyframe<Color>        ColorKeyframe;
    typedef Keyframe<Point2>       Point2Keyframe;
    typedef Keyframe<Point3>       Point3Keyframe;
    typedef Keyframe<Point4>       Point4Keyframe;
    typedef Keyframe<Rect>         RectKeyframe;
    typedef Keyframe<RectF>        RectFKeyframe;
    typedef Keyframe<Vector2>      Vector2Keyframe;
    typedef Keyframe<Vector3>      Vector3Keyframe;
    typedef Keyframe<Vector4>      Vector4Keyframe;
    typedef Keyframe<GameAssetPtr> GameAssetKeyframe;

    typedef SequenceTemplate<bool,         's', 'q', 'b', '_'> BoolSequence;
    typedef SequenceTemplate<short,        's', 'q', 's', '_'> ShortIntSequence;
    typedef SequenceTemplate<int,          's', 'q', 'i', '_'> IntSequence;
    typedef SequenceTemplate<longint,      's', 'q', 'l', '_'> LongIntSequence;
    typedef SequenceTemplate<float,        's', 'q', 'f', '_'> FloatSequence;
    typedef SequenceTemplate<double,       's', 'q', 'd', '_'> DoubleSequence;
    typedef SequenceTemplate<Color,        's', 'q', 'c', '_'> ColorSequence;
    typedef SequenceTemplate<Point2,       's', 'q', 'p', '2'> Point2Sequence;
    typedef SequenceTemplate<Point3,       's', 'q', 'p', '3'> Point3Sequence;
    typedef SequenceTemplate<Point4,       's', 'q', 'p', '4'> Point4Sequence;
    typedef SequenceTemplate<Rect,         's', 'q', 'r', '_'> RectSequence;
    typedef SequenceTemplate<RectF,        's', 'q', 'R', 'f'> RectFSequence;
    typedef SequenceTemplate<Vector2,      's', 'q', 'v', '2'> Vector2Sequence;
    typedef SequenceTemplate<Vector3,      's', 'q', 'v', '3'> Vector3Sequence;
    typedef SequenceTemplate<Vector4,      's', 'q', 'v', '4'> Vector4Sequence;
    typedef SequenceTemplate<GameAssetPtr, 's', 'q', 'a', '_'> GameAssetSequence;

    typedef SharedPointer<BoolSequence>      BoolSequencePtr;
    typedef SharedPointer<ShortIntSequence>  ShortIntSequencePtr;
    typedef SharedPointer<IntSequence>       IntSequencePtr;
    typedef SharedPointer<LongIntSequence>   LongIntSequencePtr;
    typedef SharedPointer<FloatSequence>     FloatSequencePtr;
    typedef SharedPointer<DoubleSequence>    DoubleSequencePtr;
    typedef SharedPointer<ColorSequence>     ColorSequencePtr;
    typedef SharedPointer<Point2Sequence>    Point2SequencePtr;
    typedef SharedPointer<Point3Sequence>    Point3SequencePtr;
    typedef SharedPointer<Point4Sequence>    Point4SequencePtr;
    typedef SharedPointer<RectSequence>      RectSequencePtr;
    typedef SharedPointer<RectFSequence>     RectFSequencePtr;
    typedef SharedPointer<Vector2Sequence>   Vector2SequencePtr;
    typedef SharedPointer<Vector3Sequence>   Vector3SequencePtr;
    typedef SharedPointer<Vector4Sequence>   Vector4SequencePtr;
    typedef SharedPointer<GameAssetSequence> GameAssetSequencePtr;

    template <typename T> T InterpolateKeyframe(const Keyframe<T>& k1, const Keyframe<T>& k2, float t);

    inline bool       InterpolateKeyframe(const Keyframe<bool>& k1, const Keyframe<bool>& k2, float t);
    inline GameAsset* InterpolateKeyframe(const Keyframe<GameAssetPtr>& k1, const Keyframe<GameAssetPtr>& k2, float t);

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T>
    Keyframe<T>::Keyframe()
        : Value(),
          Duration(0.0f),
          StartTime(0.0f)
    {
    }

    template <typename T>
    Keyframe<T>::Keyframe(T value, float duration)
        : Value(value),
          Duration(duration),
          StartTime(0.0f)
    {
    }

    template <typename T> T InterpolateKeyframe(const Keyframe<T>& k1, const Keyframe<T>& k2, float t)
    {
        return Math::Lerp(k1.Value, k2.Value, t);
    }

    inline bool InterpolateKeyframe(const Keyframe<bool>& k1, const Keyframe<bool>& /*k2*/, float /*t*/)
    {
        return k1.Value;
    }

    inline GameAsset* InterpolateKeyframe(const Keyframe<GameAssetPtr>& k1, const Keyframe<GameAssetPtr>& /*k2*/, float /*t*/)
    {
        return k1.Value;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T, char a, char b, char c, char d>
    SequenceTemplate<T, a, b, c, d>::SequenceTemplate()
        : startTimeChanged(true)
    {
        ResetDuration();
    }

    template <typename T, char a, char b, char c, char d>
    SequenceTemplate<T, a, b, c, d>::~SequenceTemplate()
    {
    }

    template <typename T, char a, char b, char c, char d>
    void SequenceTemplate<T, a, b, c, d>::AddKeyframe(const Keyframe<T>& item)
    {
        if (item.Duration < 0.0f)
            return;

        keyframes.push_back(item);
        startTimeChanged = true;
    }

    template <typename T, char a, char b, char c, char d>
    void SequenceTemplate<T, a, b, c, d>::InsertKeyframe(int index, const Keyframe<T>& item)
    {
        if (index < 0 || index >= GetNumberOfKeyframes())
            return;
        if (item.Duration < 0.0f)
            return;

        keyframes.insert(keyframes.begin() + index, item);
        startTimeChanged = true;
    }

    template <typename T, char a, char b, char c, char d>
    void SequenceTemplate<T, a, b, c, d>::InsertKeyframe(float time, const Keyframe<T>& item)
    {
        InsertKeyframe(GetKeyframeIndex(time), item);
    }

    template <typename T, char a, char b, char c, char d>
    void SequenceTemplate<T, a, b, c, d>::RemoveKeyframe(int index)
    {
        if (index < 0 || index >= GetNumberOfKeyframes())
            return;

        keyframes.erase(keyframes.begin() + index);
        startTimeChanged = true;
    }

    template <typename T, char a, char b, char c, char d>
    void SequenceTemplate<T, a, b, c, d>::RemoveKeyframe(float time)
    {
        const int index = GetKeyframeIndex(time);
        if (index != -1)
            RemoveKeyframe(index);
    }

    template <typename T, char a, char b, char c, char d>
    void SequenceTemplate<T, a, b, c, d>::RemoveAllKeyframes()
    {
        keyframes.clear();
        duration = 0.0f;
        startTimeChanged = false;
    }

    template <typename T, char a, char b, char c, char d>
    int SequenceTemplate<T, a, b, c, d>::GetNumberOfKeyframes() const
    {
        return static_cast<int>(keyframes.size());
    }

    template <typename T, char a, char b, char c, char d>
    const Keyframe<T>& SequenceTemplate<T, a, b, c, d>::GetKeyframe(int index)
    {
        if (startTimeChanged)
        {
            startTimeChanged = false;
            UpdateStartTimes();
        }

        return keyframes[index];
    }

    template <typename T, char a, char b, char c, char d>
    const Keyframe<T>& SequenceTemplate<T, a, b, c, d>::GetKeyframe(float time)
    {
        const int index = GetKeyframeIndex(time);
        if (index != -1)
            return GetKeyframe(index);
        else
        {
            static const Keyframe<T> Default;
            return Default;
        }
    }

    template <typename T, char a, char b, char c, char d>
    int SequenceTemplate<T, a, b, c, d>::GetKeyframeIndex(float time, int startIndex)
    {
        if (keyframes.empty())
            return -1;
        if (time <= 0.0f)
            return 0;
        if (startTimeChanged)
        {
            startTimeChanged = false;
            UpdateStartTimes();
        }

        const int numberOfKeyframes = GetNumberOfKeyframes();
        for (int i = startIndex; 0 <= i && i < numberOfKeyframes;)
        {
            const Keyframe<T>& item = keyframes[i];
            if (item.StartTime <= time && time < item.StartTime + item.Duration)
                return i;
            else
            {
                if (time < item.StartTime)
                    i--;
                else
                    i++;
            }
        }

        return numberOfKeyframes - 1;
    }

    template <typename T, char a, char b, char c, char d>
    void SequenceTemplate<T, a, b, c, d>::SetKeyframe(int index, const Keyframe<T>& item)
    {
        if (item.Duration < 0.0f)
            return;

        if (keyframes[index].Duration != item.Duration)
        {
            ResetDuration();
            startTimeChanged = true;
        }

        keyframes[index] = item;
    }

    template <typename T, char a, char b, char c, char d>
    float SequenceTemplate<T, a, b, c, d>::GetDuration()
    {
        if (duration < 0.0f)
        {
            duration = 0.0f;
            for (typename std::vector<Keyframe<T> >::const_iterator it = keyframes.begin(); it != keyframes.end(); ++it)
                duration += (*it).Duration;
        }

        return duration;
    }

    template <typename T, char a, char b, char c, char d>
    void SequenceTemplate<T, a, b, c, d>::ResetDuration()
    {
        duration = -1.0f;
    }

    template <typename T, char a, char b, char c, char d>
    void SequenceTemplate<T, a, b, c, d>::UpdateStartTimes()
    {
        float time = 0.0f;
        for (typename std::vector<Keyframe<T> >::iterator it = keyframes.begin(); it != keyframes.end(); ++it)
        {
            (*it).StartTime = time;
            time += (*it).Duration;
        }
    }

    template <typename T, char a, char b, char c, char d>
    GameAsset* SequenceTemplate<T, a, b, c, d>::Create(AssetStreamReader& reader, GameAsset* /*existingInstance*/)
    { 
        This* o = new This();
        o->duration = reader.ReadFloat();
        o->startTimeChanged = true;
        const int count = static_cast<int>(reader.ReadShortInt());
        o->keyframes.resize(count);
        for (int i = 0; i < count; i++)
        {
            reader.Read(o->keyframes[i].Value);
            o->keyframes[i].Duration = reader.ReadFloat();
        }

        return o;
    }
}

#endif