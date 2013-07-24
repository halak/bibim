namespace Bibim
{
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
            for (typename std::vector<Keyframe<T> >::const_iterator it = keyframes.begin(); it != keyframes.end(); it++)
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
        for (typename std::vector<Keyframe<T> >::iterator it = keyframes.begin(); it != keyframes.end(); it++)
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