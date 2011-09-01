namespace Bibim
{
    const SequenceDictionary::Container& SequenceDictionary::GetItems() const
    {
        return items;
    }

    bool SequenceDictionary::IsDirty() const
    {
        return isDirty;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    SequenceDictionary::KeyValuePair::KeyValuePair()
    {
    }

    SequenceDictionary::KeyValuePair::KeyValuePair(const String& key, const String& value)
        : Key(key),
          Value(value)
    {
    }

    SequenceDictionary::KeyValuePair::KeyValuePair(const KeyValuePair& original)
        : Key(original.Key),
          Value(original.Value)
    {
    }

    SequenceDictionary::KeyValuePair& SequenceDictionary::KeyValuePair::operator = (const KeyValuePair& right)
    {
        Key = right.Key;
        Value = right.Value;
        return *this;
    }

    bool SequenceDictionary::KeyValuePair::operator == (const KeyValuePair& right) const
    {
        return Key == right.Key && Value == right.Value;
    }

    bool SequenceDictionary::KeyValuePair::operator != (const KeyValuePair& right) const
    {
        return !operator == (right);
    }
}