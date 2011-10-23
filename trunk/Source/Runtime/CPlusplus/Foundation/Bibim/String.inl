#include <Bibim/Assert.h>
#include <Bibim/NullPointer.h>
#include <cstring>
#include <stdexcept>

namespace Bibim
{
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

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void String::CopyChars(char* destination, const char* source)
    {
        for (; (*source) != '\0'; destination++, source++)
            (*destination) = (*source);
    }

    void String::CopyChars(char* destination, const char* source, int length)
    {
        for (int i = 0; i < length && (*source) != '\0'; destination++, source++, i++)
            (*destination) = (*source);
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
                current = (static_cast<uint>(buffer[index + 0]) << 8) |
                          (static_cast<uint>(buffer[index + 1]) << 0);
                index += 1;
                return true;
            }
            else if (0xE0 <= first && first <= 0xEF)
            {
                BBAssertDebug(index + 2 < length);
                current = (static_cast<uint>(buffer[index + 0]) << 16) | 
                          (static_cast<uint>(buffer[index + 1]) << 8) | 
                          (static_cast<uint>(buffer[index + 2]) << 0);
                index += 2;
                return true;
            }
            else if (0xF0 <= first && first <= 0xF4)
            {
                BBAssertDebug(index + 3 < length);
                current = (static_cast<uint>(buffer[index + 0]) << 24) | 
                          (static_cast<uint>(buffer[index + 1]) << 16) | 
                          (static_cast<uint>(buffer[index + 2]) << 8) | 
                          (static_cast<uint>(buffer[index + 3]) << 0);
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
        return index + 1;
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