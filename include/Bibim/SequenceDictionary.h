#pragma once
#ifndef __BIBIM_SEQUENCEDICTIONARY_H__
#define __BIBIM_SEQUENCEDICTIONARY_H__

#   include <Bibim/FWD.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        /// @brief Sequence Container로 구현된 String Dictionary.
        /// 
        /// 값을 채우고 Optizmie한 이후에는 빠르게 검색할 수 있습니다. <br />
        /// 성능 문제상 multimap과 같이 같은 Key를 가진 Item이 여러개 존재할 수 있습니다. <br />
        class SequenceDictionary
        {
            public:
                struct KeyValuePair
                {
                    String Key;
                    String Value;

                    inline KeyValuePair();
                    inline KeyValuePair(const String& key, const String& value);
                    inline KeyValuePair(const KeyValuePair& original);

                    inline KeyValuePair& operator = (const KeyValuePair& right);
                    inline bool operator == (const KeyValuePair& right) const;
                    inline bool operator != (const KeyValuePair& right) const;
                };

                typedef std::vector<KeyValuePair> Container;

            public:
                SequenceDictionary();
                SequenceDictionary(int capacity);
                SequenceDictionary(const SequenceDictionary& original);
                ~SequenceDictionary();

                void Swap(SequenceDictionary& other);
                void Swap(Container& container);

                void Optimize();

                void Add(const String& key, const String& value);
                bool Remove(const String& key);
                bool Remove(const String& key, const String& value);
                bool Contains(const String& key) const;
                const String& Find(const String& key) const;

                inline const Container& GetItems() const;
                inline bool IsDirty() const;

                SequenceDictionary& operator = (const SequenceDictionary& right);
                bool operator == (const SequenceDictionary& right) const;
                bool operator != (const SequenceDictionary& right) const;

            private:
                Container::iterator       FindIterator(const String& key);
                Container::const_iterator FindIterator(const String& key) const;
                Container::iterator       FindIteratorSequentially(const String& key);
                Container::const_iterator FindIteratorSequentially(const String& key) const;

            private:
                Container items;
                bool isDirty;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

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

#endif