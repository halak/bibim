namespace Bibim
{
    bool Bool::Parse(const char* s)
    {
        return Parse(s, String::CharsLength(s));
    }

    bool Bool::Parse(const String& s)
    {
        return Parse(s.CStr(), s.GetLength());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    byte Byte::Parse(const char* s)
    {
        return Parse(s, String::CharsLength(s));
    }

    byte Byte::Parse(const String& s)
    {
        return Parse(s.CStr(), s.GetLength());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    short ShortInt::Parse(const char* s)
    {
        return Parse(s, String::CharsLength(s));
    }

    short ShortInt::Parse(const String& s)
    {
        return Parse(s.CStr(), s.GetLength());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    int Int::Parse(const char* s)
    {
        return Parse(s, String::CharsLength(s));
    }

    int Int::Parse(const String& s)
    {
        return Parse(s.CStr(), s.GetLength());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    longint LongInt::Parse(const char* s)
    {
        return Parse(s, String::CharsLength(s));
    }

    longint LongInt::Parse(const String& s)
    {
        return Parse(s.CStr(), s.GetLength());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    float Float::Parse(const char* s)
    {
        return Parse(s, String::CharsLength(s));
    }

    float Float::Parse(const String& s)
    {
        return Parse(s.CStr(), s.GetLength());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    double Double::Parse(const char* s)
    {
        return Parse(s, String::CharsLength(s));
    }

    double Double::Parse(const String& s)
    {
        return Parse(s.CStr(), s.GetLength());
    }
}