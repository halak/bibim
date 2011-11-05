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
        typedef unsigned char byte;
        typedef __int64       longint;
        typedef float         single;

        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // FOURCC
#       define BBMakeFOURCC(a, b, c, d) ((static_cast<int>(a) << 24) | \
                                         (static_cast<int>(b) << 16) | \
                                         (static_cast<int>(c) << 8) | \
                                         (static_cast<int>(d) << 0))
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

        // Static class : static methods�θ� �̷���� �ְ� �ν��Ͻ�ȭ(Instantiate) �� �� ���� class�� ���մϴ�.
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