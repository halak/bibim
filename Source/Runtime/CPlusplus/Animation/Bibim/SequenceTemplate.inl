#include <algorithm>

namespace Bibim
{
    template <typename T> SequenceTemplate<T>::SequenceTemplate()
        : startTimeChanged(true)
    {
        ResetDuration();
    }

    template <typename T> void SequenceTemplate<T>::AddKeyframe(const T& item)
    {
        if (item.Duration < 0.0f)
            throw std::invalid_argument("item.Duration");

        keyframes.push_back(item);
        startTimeChanged = true;
    }

    template <typename T> void SequenceTemplate<T>::InsertKeyframe(int index, const T& item)
    {
        if (index < 0 || index >= GetNumberOfKeyframes())
            throw std::out_of_range("index");
        if (item.Duration < 0.0f)
            throw std::invalid_argument("item.Duration");

        keyframes.insert(keyframes.begin() + index, item);
        startTimeChanged = true;
    }

    template <typename T> void SequenceTemplate<T>::InsertKeyframe(float time, const T& item)
    {
        InsertKeyframe(GetKeyframeIndex(time), item);
    }

    template <typename T> void SequenceTemplate<T>::RemoveKeyframe(int index)
    {
        if (index < 0 || index >= GetNumberOfKeyframes())
            throw std::out_of_range("index");

        keyframes.erase(keyframes.begin() + index);
        startTimeChanged = true;
    }

    template <typename T> void SequenceTemplate<T>::RemoveKeyframe(float time)
    {
        RemoveKeyframe(GetKeyframeIndex(time));
    }

    template <typename T> void SequenceTemplate<T>::RemoveAllKeyframes()
    {
        keyframes.clear();
        duration = 0.0f;
        startTimeChanged = false;
    }

    template <typename T> int SequenceTemplate<T>::GetNumberOfKeyframes()
    {
        return static_cast<int>(keyframes.size());
    }

    template <typename T> const T& SequenceTemplate<T>::GetKeyframe(int index)
    {
        T& item = keyframes[index];

        if (startTimeChanged)
        {
            startTimeChanged = false;
            UpdateStartTimes();
        }

        return item;
    }

    template <typename T> const T& SequenceTemplate<T>::GetKeyframe(float time)
    {
        const int index = GetKeyframeIndex(time);
        if (index != -1)
            return GetKeyframe(index);
        else
        {
            static const T Default = T();
            return Default;
        }
    }

    template <typename T> int SequenceTemplate<T>::GetKeyframeIndex(float time, int startIndex)
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
            const T& item = keyframes[i];
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

    template <typename T> void SequenceTemplate<T>::SetKeyframe(int index, const T& item)
    {
        if (item.Duration < 0.0f)
            throw std::invalid_argument("item.Duration");

        if (keyframes[index].Duration != item.Duration)
            ResetDuration();

        keyframes[index] = item;
        startTimeChanged = true;
    }

    template <typename T> float SequenceTemplate<T>::GetDuration()
    {
        if (duration < 0.0f)
        {
            duration = 0.0f;
            for (std::vector<T>::const_iterator it = keyframes.begin(); it != keyframes.end(); it++)
                duration += (*it).Duration;
        }

        return duration;
    }

    template <typename T> void SequenceTemplate<T>::ResetDuration()
    {
        duration = -1.0f;
    }

    template <typename T> void SequenceTemplate<T>::UpdateStartTimes()
    {
        float time = 0.0f;
        for (std::vector<T>::iterator it = keyframes.begin(); it != keyframes.end(); it++)
        {
            (*it).StartTime = time;
            time += (*it).Duration;
        }
    }
}