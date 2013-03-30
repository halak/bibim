namespace Bibim
{
    PropertyBase::PropertyBase(int id)
        : id(id)
    {
    }

    PropertyBase::~PropertyBase()
    {
    }

    int PropertyBase::GetID() const
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