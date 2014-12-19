#pragma once
#ifndef __BIBIM_GLES2_H__
#define __BIBIM_GLES2_H__

#include <Bibim/Foundation.h>
#if (defined(BIBIM_USE_OPENGLES2))

#ifdef __APPLE__ && __MACH__
#import <OpenGL/gl.h>
#import <OpenGL/glext.h>
#else
#if (defined(BIBIM_PLATFORM_IOS))
#    import <OpenGLES/ES2/gl.h>
#    import <OpenGLES/ES2/glext.h>
#else
#    include <GLES2/gl2.h>
#    include <EGL/egl.h>
#endif
#endif

namespace Bibim
{
    class GLES2
    {
        BBThisIsStaticClass(GLES2);
        public:
            static void CheckLastError(const char* op);
    };
}

#endif
#endif