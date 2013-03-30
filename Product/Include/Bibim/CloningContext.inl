namespace Bibim
{
    template <typename T> T* CloningContext::Clone(const T* item)
    {
        return static_cast<T*>(CloneComponent(static_cast<const GameComponent*>(item)));
    }

    template <typename T> T* CloningContext::Clone(const SharedPointer<T>& item)
    {
        return static_cast<T*>(CloneComponent(static_cast<const GameComponent*>(item.GetPointee())));
    }
}