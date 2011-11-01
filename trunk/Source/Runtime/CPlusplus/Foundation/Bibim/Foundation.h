#pragma once
#ifndef __BIBIM_FOUNDATION_H__
#define __BIBIM_FOUNDATION_H__

    namespace Bibim
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // Build Configuration
#       define BIBIM_EXCEPTION
//#     define BIBIM_USE_PRECOMPILEDHEADER

#       if (defined(WINDOWS) || defined(WIN32) || defined(WIN64))
#           define BIBIM_PLATFORM_WINDOWS
#           define BIBIM_USE_DIRECTX9
// #           define BIBIM_USE_OPENGL2
// #           define BIBIM_USE_OPENGLES2
#       else
#           define BIBIM_PLATFORM_UNKNOWN
#       endif

#       if (defined(DEBUG) || defined(_DEBUG))
#           define BIBIM_DEBUG
#       else
#           define BIBIM_RELEASE
#       endif

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // Fundamental Type Redefinition
        typedef          char    int8;
        typedef unsigned char    byte;
        typedef unsigned char    uchar;
        typedef unsigned char    uint8;
        typedef          short   int16;
        typedef unsigned short   ushort;
        typedef unsigned short   uint16;
        typedef unsigned short   word;
        typedef          int     int32;
        typedef unsigned int     uint;
        typedef unsigned int     uint32;
        typedef unsigned long    ulong;
        typedef unsigned long    dword;
        typedef          float   real32;
        typedef          double  real64;
        typedef          __int64 int64;
        typedef unsigned __int64 uint64;
        typedef unsigned __int64 qword;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // FOURCC
#       define BBMakeFOURCC(a, b, c, d) ((static_cast<uint32>(a) << 24) | \
                                         (static_cast<uint32>(b) << 16) | \
                                         (static_cast<uint32>(c) << 8) | \
                                         (static_cast<uint32>(d) << 0))
#       define BBFOURCCFirst(fourcc)    static_cast<char>((fourcc & 0xFF000000) >> 24)
#       define BBFOURCCSecond(fourcc)   static_cast<char>((fourcc & 0x00FF0000) >> 16)
#       define BBFOURCCThird(fourcc)    static_cast<char>((fourcc & 0x0000FF00) >> 8)
#       define BBFOURCCFourth(fourcc)   static_cast<char>((fourcc & 0x000000FF) >> 0)

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // Macro Functions
#       define BBStackAlloc(type, count) reinterpret_cast<type*>(_malloca(sizeof(type) * count))
#       define BBStackFree(pointer) (_freea(pointer))

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // Class Idioms

        // Static class : static methods로만 이루어져 있고 인스턴스화(Instantiate) 될 수 없는 class를 말합니다.
#       define BBThisIsStaticClass(classname)   private: \
                                                    classname(); \
                                                    classname(const classname&); \
                                                    classname& operator = (const classname&); \
                                                    ~classname();
#       define BBThisIsStaticStruct(classname)  BBThisIsStaticClass(classname) \
                                                public:
#       define BBThisIsNoncopyableClass(classname)  private: \
                                                        classname(const classname&); \
                                                        classname& operator = (const classname&);
    }

#endif