#pragma once
#ifndef __BIBIM_SEQUENCEDICTIONARY_H__
#define __BIBIM_SEQUENCEDICTIONARY_H__

#   include <Bibim/FWD.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        /// Sequence Container�� ������ String Dictionary.
        /// ���� ä��� Optizmie�� ���Ŀ��� ������ �˻��� �� �ֽ��ϴ�.
        /// ���� ������ multimap�� ���� ���� Key�� ���� Item�� ������ ������ �� �ֽ��ϴ�.
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
    }

#   include <Bibim/SequenceDictionary.inl>

#endif