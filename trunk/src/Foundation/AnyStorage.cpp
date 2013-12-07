#include <Bibim/Config.h>
#include <Bibim/AnyStorage.h>
#include <Bibim/Algorithm.h>
#include <algorithm>

namespace Bibim
{
    AnyStorage::AnyStorage()
    {
    }

    AnyStorage::~AnyStorage()
    {
    }

    void AnyStorage::AddReference(AnyStorage* item)
    {
        references.push_back(item);
    }

    void AnyStorage::RemoveReference(AnyStorage* item)
    {
        AnyStoragePtr temporaryItem = item;
        Container::Remove(references, item);
    }

    void AnyStorage::RemoveAllReferences()
    {
        references.clear();
    }

    const Any& AnyStorage::GetValue(const String& name) const
    {
        Dictionary::const_iterator it = dictionary.find(name);
        if (it != dictionary.end())
            return (*it).second;

        for (StorageCollection::const_reverse_iterator it = references.rbegin(); it != references.rend(); it++)
        {
            const Any& found = (*it)->GetValue(name);
            if (found != Any::Void)
                return found;
        }

        return Any::Void;
    }

    const Any& AnyStorage::GetValueDirect(const String& name) const
    {
        Dictionary::const_iterator it = dictionary.find(name);
        if (it != dictionary.end())
            return (*it).second;
        else
            return Any::Void;
    }

    void AnyStorage::SetValue(const String& name, const Any& value)
    {
        Dictionary::iterator it = dictionary.find(name);
        if (it != dictionary.end())
        {
            if (value != Any::Void)
                (*it).second = value;
            else
                dictionary.erase(it);
        }
        else
        {
            if (value != Any::Void)
                dictionary.insert(Dictionary::value_type(name, value));
        }
    }
}