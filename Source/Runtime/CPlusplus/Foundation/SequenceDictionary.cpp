#include <Bibim/Config.h>
#include <Bibim/SequenceDictionary.h>
#include <Bibim/Assert.h>
#include <algorithm>

namespace Bibim
{
    struct ComparePredicate
    {
        bool operator () (const SequenceDictionary::KeyValuePair& a, const SequenceDictionary::KeyValuePair& b) const
        {
            return a.Key.Compare(b.Key) < 0;
        }
    };

    SequenceDictionary::SequenceDictionary()
        : isDirty(false)
    {
    }

    SequenceDictionary::SequenceDictionary(int capacity)
        : isDirty(false)
    {
        items.reserve(capacity);
    }

    SequenceDictionary::SequenceDictionary(const SequenceDictionary& original)
        : items(original.items),
          isDirty(original.isDirty)
    {
    }

    SequenceDictionary::~SequenceDictionary()
    {
    }

    void SequenceDictionary::Swap(SequenceDictionary& other)
    {
        items.swap(other.items);
        std::swap(isDirty, other.isDirty);
    }

    void SequenceDictionary::Swap(Container& container)
    {
        items.swap(container);
        isDirty = true;
    }

    void SequenceDictionary::Optimize()
    {
        if (isDirty)
        {
            std::sort(items.begin(), items.end(), ComparePredicate());
            isDirty = false;
        }
    }

    void SequenceDictionary::Add(const String& key, const String& value)
    {
        BBAssertDebug(Contains(key) == false);
        items.push_back(KeyValuePair(key, value));
        isDirty = true;
    }

    bool SequenceDictionary::Remove(const String& key)
    {
        Container::iterator it;

        if (IsDirty() == false)
            it = FindIterator(key);
        else
            it = FindIteratorSequentially(key);

        if (it != items.end())
        {
            items.erase(it);
            return true;
        }
        else
            return false;
    }

    bool SequenceDictionary::Remove(const String& key, const String& value)
    {
        Container::iterator it;

        if (IsDirty() == false)
        {
            it = FindIterator(key);

            for (/**/; it != items.end() && (*it).Key == key; it++)
            {
                if ((*it).Value == value)
                {
                    items.erase(it);
                    return true;
                }
            }

            return false;
        }
        else
        {
            it = FindIteratorSequentially(key);

            for (/**/; it != items.end(); it++)
            {
                if ((*it).Key == key && (*it).Value == value)
                {
                    items.erase(it);
                    return true;
                }
            }

            return false;
        }
    }

    bool SequenceDictionary::Contains(const String& key) const
    {
        if (IsDirty() == false)
            return FindIterator(key) != items.end();
        else
            return FindIteratorSequentially(key) != items.end();
    }

    const String& SequenceDictionary::Find(const String& key) const
    {
        Container::const_iterator it;

        if (IsDirty() == false)
            it = FindIterator(key);
        else
            it = FindIteratorSequentially(key);

        if (it != items.end())
            return (*it).Value;
        else
            return String::Empty;
    }

    SequenceDictionary::Container::iterator SequenceDictionary::FindIterator(const String& key)
    {
        Container::iterator it = std::lower_bound(items.begin(), items.end(), KeyValuePair(key, String::Empty), ComparePredicate());
        if (it != items.end() && (*it).Key == key)
            return it;
        else
            return items.end();
    }

    SequenceDictionary::Container::const_iterator SequenceDictionary::FindIterator(const String& key) const
    {
        Container::const_iterator it = std::lower_bound(items.begin(), items.end(), KeyValuePair(key, String::Empty), ComparePredicate());
        if (it != items.end() && (*it).Key == key)
            return it;
        else
            return items.end();
    }

    SequenceDictionary::Container::iterator SequenceDictionary::FindIteratorSequentially(const String& key)
    {
        for (Container::iterator it = items.begin(); it != items.end(); it++)
        {
            if ((*it).Key == key)
                return it;
        }

        return items.end();
    }

    SequenceDictionary::Container::const_iterator SequenceDictionary::FindIteratorSequentially(const String& key) const
    {
        for (Container::const_iterator it = items.begin(); it != items.end(); it++)
        {
            if ((*it).Key == key)
                return it;
        }

        return items.end();
    }

    SequenceDictionary& SequenceDictionary::operator = (const SequenceDictionary& right)
    {
        items = right.items;
        isDirty = right.isDirty;
        return *this;
    }

    bool SequenceDictionary::operator == (const SequenceDictionary& right) const
    {
        return items == right.items && isDirty == right.isDirty;
    }

    bool SequenceDictionary::operator != (const SequenceDictionary& right) const
    {
        return !operator == (right);
    }
}