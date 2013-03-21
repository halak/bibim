#pragma once
#ifndef __BIBIM_GLES2_H__
#define __BIBIM_GLES2_H__

#   include <Bibim/Foundation.h>
#   include <GLES2/gl2.h>
#   include <EGL/egl.h>

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