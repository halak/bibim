#ifndef __BIBIM_RANGE_INL__
#define __BIBIM_RANGE_INL__

    namespace Bibim
    {
        template <typename T> Range<T>::Range()
        {
        }

        template <typename T> Range<T>::Range(T min, T max)
            : Min(min),
              Max(max)
        {
        }

        template <typename T> Range<T>::Range(const Range<T>& original)
            : Min(original.Min),
              Max(original.Max)
        {
        }

        template <typename T> Range<T>& Range<T>::operator = (const Range<T>& right)
        {
            Min = right.Min;
            Max = right.Max;
            return *this;
        }

        template <typename T> bool Range<T>::operator == (const Range<T>& right) const
        {
            return Min == right.Min && Max == right.Max;
        }

        template <typename T> bool Range<T>::operator != (const Range<T>& right) const
        {
            return !operator == (right);
        }
    }

#endif