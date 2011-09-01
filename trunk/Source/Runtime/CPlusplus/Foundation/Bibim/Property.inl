namespace Bibim
{
    PropertyBase::PropertyBase(uint32 id)
        : id(id)
    {
    }

    PropertyBase::~PropertyBase()
    {
    }

    uint32 PropertyBase::GetID() const
    {
        return id;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    template <typename T> Property<T>::~Property()
    {
        delete getterAndSetter;
    }

    template <typename T> T Property<T>::GetValue(void* instance) const
    {
        return getterAndSetter->GetValue(instance);
    }

    template <typename T> void Property<T>::SetValue(void* instance, T value) const
    {
        getterAndSetter->SetValue(instance, value);
    }
}