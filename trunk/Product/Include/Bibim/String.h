#pragma once
#ifndef __BIBIM_STRING_H__
#define __BIBIM_STRING_H__

#   include <Bibim/Foundation.h>
#   include <Bibim/Assert.h>
#   include <Bibim/NullPointer.h>
#   include <Bibim/SharedObject.h>
#   include <Bibim/SharedPointer.h>
#   include <cstring>

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
                static String CFormat(const char* format, ...);

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
                bool Equals(const char* right, int length) const;
                bool Equals(const String& right) const;
                bool EqualsIgnoreCase(const char* right) const;
                bool EqualsIgnoreCase(const char* right, int length) const;
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

                int Count(char c) const;

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

                static inline bool IsWhiteSpace(int c);
                static inline int CopyChars(char* destination, const char* source);
                static inline int CopyChars(char* destination, const char* source, int length);
                static inline int CompareCharsIgnoreCase(const char* a, const char* b);
                static inline bool EqualsCharsIgnoreCase(const char* a, const char* b);
                static inline int CharsLength(const char* s);
                static inline int CharsFind(const char* s, char c);

            public:
                static const String Empty;
                static const String NewLine;
                static const int UTF8BOMLength = 3;
                static const byte UTF8BOM[UTF8BOMLength];
                static inline bool CheckUTF8BOM(byte a, byte b, byte c);
                static inline bool CheckUTF8BOM(char a, char b, char c);

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
                        inline const char* GetBuffer() const;
                        inline int GetLength() const;

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

                explicit String(int length);

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
                    explicit StringBuffer(int length);
                    inline virtual ~StringBuffer();

                    inline StringBuffer& operator = (const StringBuffer& right);

                    void Initialize(const char* s, int length);
                    void UpdateHashCode();

                    char* s;
                    int length;
                    int hashCode;
                };

            private:
                SharedPointer<StringBuffer> buffer;
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        String::String()
            : buffer(Empty.buffer)
        {
        }

        String::String(const char* s)
            : buffer((s && s[0] != '\0') ? SharedPointer<StringBuffer>(new StringBuffer(s)) : Empty.buffer)
        {
        }

        String::String(const String& original)
            : buffer(original.buffer)
        {
        }

        String::String(const String& original, int startIndex)
        {
            if (original.buffer->length > startIndex)
                buffer.Reset(new StringBuffer(&original.buffer->s[startIndex]));
            else
                buffer = Empty.buffer;
        }

        String::String(const String& original, int startIndex, int length)
        {
            if (original.buffer->length > startIndex)
            {
                if (startIndex + length <= original.buffer->length)
                    buffer.Reset(new StringBuffer(&original.buffer->s[startIndex], length));
                else
                    buffer.Reset(new StringBuffer(&original.buffer->s[startIndex], original.buffer->length - startIndex));
            }
            else
                buffer = Empty.buffer;
        }

        String::~String()
        {
        }

        int String::ReverseFind(char c) const
        {
            return buffer->length > 0 ? ReverseFind(c, buffer->length - 1) : -1;
        }

        int String::ReverseFind(const char* s) const
        {
            return buffer->length > 0 ? ReverseFind(s, buffer->length - 1) : -1;
        }

        int String::ReverseFind(const String& s) const
        {
            return buffer->length > 0 ? ReverseFind(s, buffer->length - 1) : -1;
        }

        int String::ReverseFindIgnoreCase(char c) const
        {
            return buffer->length > 0 ? ReverseFindIgnoreCase(c, buffer->length - 1) : -1;
        }

        int String::ReverseFindIgnoreCase(const char* s) const
        {
            return buffer->length > 0 ? ReverseFindIgnoreCase(s, buffer->length - 1) : -1;
        }

        int String::ReverseFindIgnoreCase(const String& s) const
        {
            return buffer->length > 0 ? ReverseFindIgnoreCase(s, buffer->length - 1) : -1;
        }

        const char* String::CStr() const
        {
            return buffer->s;
        }

        const char* String::GetCharPointer() const
        {
            return buffer->s;
        }

        int String::GetLength() const
        {
            return buffer->length;
        }

        bool String::IsEmpty() const
        {
            return buffer->length == 0;
        }

        String& String::operator = (char right)
        {
            if (right != '\0')
            {
                const char s[] = { right, '\0' };
                buffer.Reset(new StringBuffer(s, 1));
            }
            else
                buffer = Empty.buffer;

            return *this;
        }

        String& String::operator = (const char* right)
        {
            if (right && right[0] != '\0')
                buffer.Reset(new StringBuffer(right));
            else
                buffer = Empty.buffer;

            return *this;
        }

        String& String::operator = (const String& right)
        {
            buffer = right.buffer;
            return *this;
        }

        String& String::operator += (char right)
        {
            const char s[] = { right, '\0' };
            Append(s);
            return *this;
        }

        String& String::operator += (const char* right)
        {
            Append(right);
            return *this;
        }

        String& String::operator += (const String& right)
        {
            Append(right);
            return *this;
        }

        String String::operator + (char right) const
        {
            const char s[] = { right, '\0' };
            return String(AppendTag(), buffer->s, buffer->length, s, 1);
        }

        String String::operator + (const char* right) const
        {
            return String(AppendTag(), buffer->s, buffer->length, right, -1);
        }

        String String::operator + (const String& right) const
        {
            return String(AppendTag(), buffer->s, buffer->length, right.buffer->s, right.buffer->length);
        }

        bool String::operator == (const char* right) const
        {
            return Equals(right);
        }

        bool String::operator == (const String& right) const
        {
            return Equals(right);
        }

        bool String::operator != (const char* right) const
        {
            return !Equals(right);
        }

        bool String::operator != (const String& right) const
        {
            return !Equals(right);
        }

        bool String::operator < (const char* right) const
        {
            return Compare(right) < 0;
        }

        bool String::operator < (const String& right) const
        {
            return Compare(right) < 0;
        }

        bool String::operator > (const char* right) const
        {
            return Compare(right) > 0;
        }

        bool String::operator > (const String& right) const
        {
            return Compare(right) > 0;
        }

        bool String::operator <= (const char* right) const
        {
            return Compare(right) <= 0;
        }

        bool String::operator <= (const String& right) const
        {
            return Compare(right) <= 0;
        }

        bool String::operator >= (const char* right)
        {
            return Compare(right) >= 0;
        }

        bool String::operator >= (const String& right) const
        {
            return Compare(right) >= 0;
        }

        String::CharRef String::operator [] (int index)
        {
            BBAssertDebug(0 <= index && index < buffer->length);
            return CharRef(*this, index);
        }

        char String::operator [] (int index) const
        {
            BBAssertDebug(0 <= index && index < buffer->length);
            return buffer->s[index];
        }

        bool operator == (const char* left, const String& right)
        {
            return right == left;
        }

        bool operator != (const char* left, const String& right)
        {
            return right != left;
        }

        bool operator < (const char* left, const String& right)
        {
            return right > left;
        }

        bool operator > (const char* left, const String& right)
        {
            return right < left;
        }

        bool operator <= (const char* left, const String& right)
        {
            return right >= left;
        }

        bool operator >= (const char* left, const String& right)
        {
            return right <= left;
        }

        String operator + (const char* left, const String& right)
        {
            return String(String::AppendTag(), left, String::CharsLength(left), right.CStr(), right.GetLength());
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        bool String::IsWhiteSpace(int c)
        {
            return (c == 0x20 ||
                    c == 0x09 ||
                    c == 0x0A ||
                    c == 0x0B ||
                    c == 0x0C ||
                    c == 0x0D ||
                    c == 0x85 ||
                    c == 0xA0);
        }

        int String::CopyChars(char* destination, const char* source)
        {
            int i = 0;
            for (; (*source) != '\0'; destination++, source++, i++)
                (*destination) = (*source);
            return i;
        }

        int String::CopyChars(char* destination, const char* source, int length)
        {
            int i = 0;
            for (i = 0; i < length && (*source) != '\0'; destination++, source++, i++)
                (*destination) = (*source);
            return i;
        }


    
        int String::CompareCharsIgnoreCase(const char* a, const char* b)
        {
    #   if (defined(BIBIM_PLATFORM_WINDOWS))
            return _stricmp(a, b);
    #   elif (defined(BIBIM_PLATFORM_UNIX))
            return strcasecmp(a, b);
    #   endif
        }

        bool String::EqualsCharsIgnoreCase(const char* a, const char* b)
        {
            return CompareCharsIgnoreCase(a, b) == 0;
        }

        int String::CharsLength(const char* s)
        {
            int result = 0;
            while (*s++ != '\0') { result++; }
            return result;
        }

        int String::CharsFind(const char* s, char c)
        {
            int result = 0;
            for (; *s != '\0'; s++, result++)
            {
                if (*s == c)
                    return result;
            }
            return -1;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        bool String::CheckUTF8BOM(byte a, byte b, byte c)
        {
            return UTF8BOM[0] == a && UTF8BOM[1] == b && UTF8BOM[2] == c;
        }

        bool String::CheckUTF8BOM(char a, char b, char c)
        {
            return CheckUTF8BOM(static_cast<byte>(a), static_cast<byte>(b), static_cast<byte>(c));
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        String::CharRef::CharRef(String& s, int index)
            : s(s),
              index(index)
        {
        }

        String::CharRef::CharRef(const CharRef& original)
            : s(original.s),
              index(original.index)
        {
        }

        String::CharRef& String::CharRef::operator = (char c)
        {
            if (s.buffer.GetReferenceCount() > 1)
                s.buffer.Reset(new StringBuffer(*s.buffer));

            s.buffer->s[index] = c;

            return *this;
        }

        String::CharRef::operator char () const
        {
            return s.buffer->s[index];
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        String::UTF8CharEnumerator::UTF8CharEnumerator(const char* s)
            : s(s),
              length(static_cast<int>(strlen(s))),
              index(-1),
              current(0)
        {
        }

        String::UTF8CharEnumerator::UTF8CharEnumerator(const char* s, int length)
            : s(s),
              length(length),
              index(-1),
              current(0)
        {
        }

        String::UTF8CharEnumerator::UTF8CharEnumerator(const String& s)
            : s(s.buffer->s),
              length(s.GetLength()),
              index(-1),
              current(0)
        {
        }

        String::UTF8CharEnumerator::UTF8CharEnumerator(const UTF8CharEnumerator& original)
            : s(original.s),
              length(original.length),
              index(original.index),
              current(original.current)
        {
        }

        void String::UTF8CharEnumerator::Reset()
        {
            index = -1;
            current = 0;
        }

        bool String::UTF8CharEnumerator::MoveNext()
        {
            index++;

            if (index < length)
            {
                const byte* buffer = reinterpret_cast<const byte*>(s);

                byte first = buffer[index];
                if (first <= 0x7F)
                {
                    current = first;
                    return true;
                }
                else if (0xC2 <= first && first <= 0xDF)
                {
                    BBAssertDebug(index + 1 < length);
                    current = (static_cast<int>(buffer[index + 0]) << 8) |
                              (static_cast<int>(buffer[index + 1]) << 0);
                    index += 1;
                    return true;
                }
                else if (0xE0 <= first && first <= 0xEF)
                {
                    BBAssertDebug(index + 2 < length);
                    current = (static_cast<int>(buffer[index + 0]) << 16) | 
                              (static_cast<int>(buffer[index + 1]) << 8) | 
                              (static_cast<int>(buffer[index + 2]) << 0);
                    index += 2;
                    return true;
                }
                else if (0xF0 <= first && first <= 0xF4)
                {
                    BBAssertDebug(index + 3 < length);
                    current = (static_cast<int>(buffer[index + 0]) << 24) | 
                              (static_cast<int>(buffer[index + 1]) << 16) | 
                              (static_cast<int>(buffer[index + 2]) << 8) | 
                              (static_cast<int>(buffer[index + 3]) << 0);
                    index += 3;
                    return true;
                }
                else
                    return false; // Invalid Character
            }
            else
                return false;
        }

        int String::UTF8CharEnumerator::GetCurrent() const
        {
            return current;
        }

        int String::UTF8CharEnumerator::GetCurrentIndex() const
        {
            return index;
        }

        const char* String::UTF8CharEnumerator::GetBuffer() const
        {
            return s;
        }

        int String::UTF8CharEnumerator::GetLength() const
        {
            return length;
        }

        String::UTF8CharEnumerator& String::UTF8CharEnumerator::operator = (const UTF8CharEnumerator& right)
        {
            s = right.s;
            length = right.length;
            index = right.index;
            current = right.current;
            return *this;
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////

        String::StringBuffer::StringBuffer(const char* s, int length)
            : s(nullptr),
              length(0),
              hashCode(0)
        {
            Initialize(s, length);
        }

        String::StringBuffer::StringBuffer(const StringBuffer& original)
            : s(nullptr),
              length(0),
              hashCode(0)
        {
            Initialize(original.s, original.length);
        }

        String::StringBuffer::~StringBuffer()
        {
            delete [] s;
        }

        String::StringBuffer& String::StringBuffer::operator = (const StringBuffer& right)
        {
            delete [] s;
            Initialize(right.s, right.length);
            return *this;
        }
    }

#endif