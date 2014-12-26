#pragma once
#ifndef __BIBIM_FOUNDATION_H__
#define __BIBIM_FOUNDATION_H__

#include <Bibim/Config.h>

namespace Bibim
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Fundamental Type Redefinition
    typedef unsigned char byte;
    typedef long long     longint;
    typedef float         single;

    typedef unsigned char       uchar;
    typedef unsigned short      ushort;
    typedef unsigned int        uint;
    typedef unsigned long       ulong;
    typedef long long           int64;
    typedef unsigned long long  uint64;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // FOURCC
#   define BBMakeFOURCC(a, b, c, d) ((static_cast<int>(a) << 24) | \
                                     (static_cast<int>(b) << 16) | \
                                     (static_cast<int>(c) << 8) | \
                                     (static_cast<int>(d) << 0))
#   define BBFOURCCFirst(fourcc)    static_cast<char>((fourcc & 0xFF000000) >> 24)
#   define BBFOURCCSecond(fourcc)   static_cast<char>((fourcc & 0x00FF0000) >> 16)
#   define BBFOURCCThird(fourcc)    static_cast<char>((fourcc & 0x0000FF00) >> 8)
#   define BBFOURCCFourth(fourcc)   static_cast<char>((fourcc & 0x000000FF) >> 0)

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // Macro Functions
#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       define BBStackAlloc(type, count) reinterpret_cast<type*>(_malloca(sizeof(type) * (count)))
#       define BBStackFree(pointer) (_freea(pointer))
#   else
#       define BBStackAlloc(type, count) (new type [count])
#       define BBStackFree(pointer) (delete [] pointer)
#   endif

#   define BBUnusedParameter(variable) { variable = variable; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Class Idioms

    // Static class : static methods로만 이루어져 있고 인스턴스화(Instantiate) 될 수 없는 class를 말합니다.
#   define BBThisIsStaticClass(classname)   private: \
                                                classname(); \
                                                classname(const classname&); \
                                                classname& operator = (const classname&); \
                                                ~classname();
#   define BBThisIsStaticStruct(classname)  BBThisIsStaticClass(classname) \
                                            public:
#   define BBThisIsNoncopyableClass(classname)  private: \
                                                    classname(const classname&); \
                                                    classname& operator = (const classname&);
}

#if (defined(__APPLE__))
#    include <cstddef>
#    include <cstdlib>
#    include <cstdio>
#    include <string.h>
#    include <strings.h>
#    include <iostream>
#endif

#if (defined(BIBIM_PLATFORM_WINDOWS))
#    include <malloc.h>
#endif

#endif