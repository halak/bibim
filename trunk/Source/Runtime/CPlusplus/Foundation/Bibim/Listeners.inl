namespace Bibim
{
    template <typename T> Listeners<T>::Listeners()
    {
    }

    template <typename T> Listeners<T>::Listeners(int capacity)
    {
        items.reserve(capacity);
        objects.reserve(capacity);
    }

    template <typename T> Listeners<T>::~Listeners()
    {
    }

    template <typename T> void Listeners<T>::Add(T* item)
    {
        Add(item, nullptr);
    }

    template <typename T> void Listeners<T>::Add(T* item, SharedObject* obj)
    {
        if (item == nullptr)
            return;

        items.push_back(item);
        objects.push_back(obj);
    }

    template <typename T> bool Listeners<T>::Remove(T* item)
    {
        const int count = static_cast<int>(items.size());
        for (int i = 0; i < count; i++)
        {
            if (items[i] == item)
            {
                items.erase(items.begin() + i);
                objects.erase(objects.begin() + i);
                return true;
            }
        }

        return false;
    }

    template <typename T> void Listeners<T>::Clear()
    {
        items.clear();
        objects.clear();
    }

    template <typename T> typename Listeners<T>::Iterator Listeners<T>::Begin() const
    {
        return items.begin();
    }

    template <typename T> typename Listeners<T>::Iterator Listeners<T>::End() const
    {
        return items.end();
    }
}