#include <Bibim/ICloneable.h>

namespace Bibim
{
    template <typename T> T* CloningContext::CloneActually(T* original, T* fallback)
    {
        if (original == nullptr)
            return nullptr;

        if (ICloneable* cloneableOriginal = dynamic_cast<ICloneable*>(original))
        {
            std::map<ICloneable*, ICloneable*>::iterator it = clones.find(cloneableOriginal);
            if (it != clones.end())
                return dynamic_cast<T*>((*it).second);
            else
            {
                ICloneable* clone = cloneableOriginal->Clone();
                clones.insert(std::map<ICloneable*, ICloneable*>::value_type(cloneableOriginal, clone));
                return dynamic_cast<T*>(clone);
            }
        }
        else
            return fallback;
    }

    template <typename T> SharedPointer<T> CloningContext::CloneActually(SharedPointer<T> original, SharedPointer<T> fallback)
    {
        if (original == nullptr)
            return nullptr;

        if (ICloneablePtr cloneableOriginal = DynamicCast<ICloneable>(original))
        {
            std::map<ICloneablePtr, ICloneablePtr>::iterator it = sharedClones.find(cloneableOriginal);
            if (it != sharedClones.end())
                return DynamicCast<T>((*it).second);
            else
            {
                ICloneablePtr clone = cloneableOriginal->Clone();
                sharedClones.insert(std::map<ICloneablePtr, ICloneablePtr>::value_type(cloneableOriginal, clone));
                return DynamicCast<T>(clone);
            }
        }
        else
            return fallback;
    }

    template <typename T> T* CloningContext::Clone(T* original)
    {
        return CloneActually(original, original);
    }

    template <typename T> T* CloningContext::CloneOrNull(T* original)
    {
        return CloneActually(original, nullptr);
    }

    template <typename T> SharedPointer<T> CloningContext::Clone(SharedPointer<T> original)
    {
        return CloneActually(original, original);
    }

    template <typename T> SharedPointer<T> CloningContext::CloneOrNull(SharedPointer<T> original)
    {
        return CloneActually(original, nullptr);
    }

    template <typename T> WeakPointer<T> CloningContext::Clone(WeakPointer<T> original)
    {
        return CloneActually(original.Lock(), original.Lock());
    }

    template <typename T> WeakPointer<T> CloningContext::CloneOrNull(WeakPointer<T> original)
    {
        return CloneActually(original.Lock(), nullptr);
    }
}