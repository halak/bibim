#pragma once
#ifndef __BIBIM_PATH_H__
#define __BIBIM_PATH_H__

#include <Bibim/FWD.h>
#include <Bibim/String.h>

namespace Bibim
{
    class Path
    {
        BBThisIsStaticClass(Path);
        public:
            static inline String Combine(const String& a, const String& b);
            static inline String Combine(const String& a, const String& b, const String& c);
            static inline String Combine(const String& a, const String& b, const String& c, const String& d);
            static String Combine(const String& a, const String& b, const String& c, const String& d, const String& e);
            static String GetDirectory(const String& path);
            static bool IsAbsolutePath(const String& path);
    };

    String Path::Combine(const String& a, const String& b)
    {
        return Combine(a, b, String::Empty, String::Empty, String::Empty);
    }

    String Path::Combine(const String& a, const String& b, const String& c)
    {
        return Combine(a, b, c, String::Empty, String::Empty);
    }

    String Path::Combine(const String& a, const String& b, const String& c, const String& d)
    {
        return Combine(a, b, c, d, String::Empty);
    }
}

#endif