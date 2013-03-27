#pragma once
#ifndef __BIBIM_FOUNDATION_H__
#define __BIBIM_FOUNDATION_H__

    namespace Bibim
    {
        ////////////////////////////////////////////////////////////////////////////////////////////////////
        // Build Configuration
//#     define BIBIM_USE_PRECOMPILEDHEADER

#       if (defined(WINDOWS) || defined(WIN32) || defined(WIN64))
#           define BIBIM_PLATFORM_WINDOWS
// #        define BIBIM_USE_DIRECTX9
// #        define BIBIM_USE_OPENGL2
// #        define BIBIM_USE_OPENGLES2
#       elif (defined(ANDROID))
#           define BIBIM_PLATFORM_UNIX
#           define BIBIM_PLATFORM_ANDROID
#       elif (defined(__APPLE__))
#           define BIBIM_PLATFORM_UNIX
#           define BIBIM_PLATFORM_IOS
#           define BIBIM_USE_OPENGLES2
#       else
#           error "UNKNOWN PLATFORM"
#           define BIBIM_PLATFORM_UNKNOWN
#       endif

#       if (defined(DEBUG) || defined(_DEBUG))
#           define BIBIM_DEBUG
#       else
#           define BIBIM_RELEASE
#       endif

#       if (defined(_MSC_VER))
#           define BIBIM_COMPILER_MSVC
#       else
#           define BIBIM_COMPILER_GCC
#       endif

#       if (defined(_MSC_VER) && _MSC_VER > 1500)
#           define BIBIM_CPLUSPLUS_0X
#       endif
        
#       if (defined(APPLE_LLVM_COMPILER))
#           define BIBIM_CPLUSPLUS_0X
#       endif

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
#       if (defined(BIBIM_PLATFORM_WINDOWS))
#           define BBStackAlloc(type, count) reinterpret_cast<type*>(_malloca(sizeof(type) * (count)))
#           define BBStackFree(pointer) (_freea(pointer))
#       else
#           define BBStackAlloc(type, count) (new type [count])
#           define BBStackFree(pointer) (delete [] pointer)
#       endif

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

#if (defined(__APPLE__))
#    include <iostream>
#endif

#endif