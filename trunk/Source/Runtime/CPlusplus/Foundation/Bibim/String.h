#pragma once
#ifndef __BIBIM_STRING_H__
#define __BIBIM_STRING_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/SharedPointer.h>

    namespace Bibim
    {
        class String
        {
            public:
                class CharRef;

            public:
                inline String();
                inline String(const char* s);
                String(const char* s, int startIndex);
                String(const char* s, int startIndex, int length);
                inline String(const String& original);
                inline String(const String& original, int startIndex);
                inline String(const String& original, int startIndex, int length);
                inline ~String();

                void Append(const char* s);
                void Append(const char* s, int length);
                void Append(const String& s);

                void Insert(int index, const char* s);
                void Insert(int index, const String& s);

                void Replace(char oldValue, char newValue);

                void Trim();

                void ToLower();
                void ToUpper();

                int Compare(const char* right) const;
                int Compare(const String& right) const;
                int CompareIgnoreCase(const char* right) const;
                int CompareIgnoreCase(const String& right) const;

                bool Equals(const char* right) const;
                bool Equals(const String& right) const;
                bool EqualsIgnoreCase(const char* right) const;
                bool EqualsIgnoreCase(const String& right) const;

                bool Contains(char c) const;
                bool Contains(const char* s) const;
                bool Contains(const String& s) const;
                bool ContainsIgnoreCase(char c) const;
                bool ContainsIgnoreCase(const char* s) const;
                bool ContainsIgnoreCase(const String& s) const;

                bool StartsWith(const char* s) const;
                bool StartsWith(const String& s) const;
                bool StartsWithIgnoreCase(const char* s) const;
                bool StartsWithIgnoreCase(const String& s) const;

                bool EndsWith(const char* s) const;
                bool EndsWith(const String& s) const;
                bool EndsWithIgnoreCase(const char* s) const;
                bool EndsWithIgnoreCase(const String& s) const;

                int Find(char c, int index = 0) const;
                int Find(const char* s, int index = 0) const;
                int Find(const String& s, int index = 0) const;
                int FindIgnoreCase(char c, int index = 0) const;
                int FindIgnoreCase(const char* s, int index = 0) const;
                int FindIgnoreCase(const String& s, int index = 0) const;

                inline int ReverseFind(char c) const;
                inline int ReverseFind(const char* s) const;
                inline int ReverseFind(const String& s) const;
                inline int ReverseFindIgnoreCase(char c) const;
                inline int ReverseFindIgnoreCase(const char* s) const;
                inline int ReverseFindIgnoreCase(const String& s) const;
                int ReverseFind(char c, int index) const;
                int ReverseFind(const char* s, int index) const;
                int ReverseFind(const String& s, int index) const;
                int ReverseFindIgnoreCase(char c, int index) const;
                int ReverseFindIgnoreCase(const char* s, int index) const;
                int ReverseFindIgnoreCase(const String& s, int index) const;

                String Substring(int startIndex) const;
                String Substring(int startIndex, int length) const;

                inline const char* CStr() const;
                inline const char* GetCharPointer() const;
                inline int GetLength() const;

                inline bool IsEmpty() const;

                inline String& operator = (char right);
                inline String& operator = (const char* right);
                inline String& operator = (const String& right);
                inline String& operator += (char right);
                inline String& operator += (const char* right);
                inline String& operator += (const String& right);

                inline String operator + (char right) const;
                inline String operator + (const char* right) const;
                inline String operator + (const String& right) const;

                inline bool operator == (const char* right) const;
                inline bool operator == (const String& right) const;
                inline bool operator != (const char* right) const;
                inline bool operator != (const String& right) const;
                inline bool operator < (const char* right) const;
                inline bool operator < (const String& right) const;
                inline bool operator > (const char* right) const;
                inline bool operator > (const String& right) const;
                inline bool operator <= (const char* right) const;
                inline bool operator <= (const String& right) const;
                inline bool operator >= (const char* right);
                inline bool operator >= (const String& right) const;

                inline CharRef operator [] (int index);
                inline char    operator [] (int index) const;

                friend inline bool operator == (const char* left, const String& right);
                friend inline bool operator != (const char* left, const String& right);
                friend inline bool operator <  (const char* left, const String& right);
                friend inline bool operator >  (const char* left, const String& right);
                friend inline bool operator <= (const char* left, const String& right);
                friend inline bool operator >= (const char* left, const String& right);
                friend inline String operator + (const char* left, const String& right);

                static inline int CopyChars(char* destination, const char* source);
                static inline int CopyChars(char* destination, const char* source, int length);
                static inline int CharsLength(const char* s);

            public:
                static const String Empty;
                static const byte UTF8BOM[3];

            public:
                class CharRef
                {
                    friend class String;
                    public:
                        inline CharRef(const CharRef& original);

                        inline CharRef& operator = (char c);

                        inline operator char () const;

                    private:
                        inline CharRef(String& s, int index);

                    private:
                        String& s;
                        int index;

                    private:
                        CharRef& operator = (const CharRef& right);
                };

                class UTF8CharEnumerator
                {
                    public:
                        inline UTF8CharEnumerator(const char* s);
                        inline UTF8CharEnumerator(const char* s, int length);
                        inline UTF8CharEnumerator(const String& s);
                        inline UTF8CharEnumerator(const UTF8CharEnumerator& original);

                        inline void Reset();
                        inline bool MoveNext();

                        inline int GetCurrent() const;
                        inline int GetCurrentIndex() const;

                        inline UTF8CharEnumerator& operator = (const UTF8CharEnumerator& right);

                    private:
                        const char* s;
                        int length;

                        int index;
                        int current;
                };

                typedef UTF8CharEnumerator CharEnumerator;

            private:
                struct EmptyStringTag {};
                String(EmptyStringTag);

                struct AppendTag {};
                String(AppendTag, const char* s1, int length1, const char* s2, int length2);

                struct InsertTag {};
                inline void Insert(int index, const char* s, int length);

                inline bool ContainsTemplate(const char* s, int length) const;
                inline bool ContainsIgnoreCaseTemplate(const char* s, int length) const;
                inline bool StartsWithTemplate(const char* s, int length) const;
                inline bool StartsWithIgnoreCaseTemplate(const char* s, int length) const;
                inline bool EndsWithTemplate(const char* s, int length) const;
                inline bool EndsWithIgnoreCaseTemplate(const char* s, int length) const;
                inline int FindTemplate(const char* s, int length, int index) const;
                inline int FindIgnoreCaseTemplate(const char* s, int length, int index) const;
                inline int ReverseFindTemplate(const char* s, int length, int index) const;
                inline int ReverseFindIgnoreCaseTemplate(const char* s, int length, int index) const;

            private:
                struct StringBuffer : public SharedObject
                {
                    StringBuffer(const char* s);
                    inline StringBuffer(const char* s, int length);
                    inline StringBuffer(const StringBuffer& original);
                    StringBuffer(EmptyStringTag);
                    StringBuffer(InsertTag, const char* s1, int length1, int index, const char* s2, int length2);
                    inline virtual ~StringBuffer();

                    inline StringBuffer& operator = (const StringBuffer& right);

                    void Initialize(const char* s, int length);

                    char* s;
                    int length;
                    int hashCode;
                };

            private:
                SharedPointer<StringBuffer> buffer;
        };
    }

#   include <Bibim/String.inl>

#endif