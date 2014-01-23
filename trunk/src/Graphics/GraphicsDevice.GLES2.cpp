#include <Bibim/Config.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/Assert.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/Color.h>
#include <Bibim/GLES2.h>
#include <Bibim/Log.h>
#include <Bibim/RenderTargetTexture2D.GLES2.h>
#include <Bibim/Window.h>
#include <algorithm>

namespace Bibim
{
    GraphicsDevice::GraphicsDevice()
        : fullscreen(false)
    {
#       if (defined(BIBIM_USE_EGL))
        eglDisplay = nullptr;
        eglSurface = nullptr;
        eglContext = nullptr;
#       endif
    }

    GraphicsDevice::~GraphicsDevice()
    {
        Finalize();
    }

    void GraphicsDevice::Clear()
    {
        Clear(Color::CornflowerBlue);
    }

    void GraphicsDevice::Clear(Color color)
    {
        const Vector4 colorVector = color.ToVector4();
        glClearColor(colorVector.X, colorVector.Y, colorVector.Z, colorVector.W);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    bool GraphicsDevice::BeginDraw()
    {
        Reset();
        return true;
    }

    bool GraphicsDevice::BeginDraw(RenderTargetTexture2D* /*renderTarget*/)
    {
        return true;
    }

    void GraphicsDevice::EndDraw()
    {
    }

    void GraphicsDevice::EndDraw(RenderTargetTexture2D* /*renderTarget*/)
    {
    }

    void GraphicsDevice::Present()
    {
#       if (defined(BIBIM_USE_EGL))
        eglSwapBuffers(eglDisplay, eglSurface);
#       endif
    }

    void GraphicsDevice::SetFullscreen(bool value)
    {
        if (GetFullscreen() != value)
        {
            fullscreen = value;

            // TODO: Reinitialize Device
        }
    }

    Point2 GraphicsDevice::GetViewportSize() const
    {
        if (Window* window = GetWindow())
            return window->GetSize();
        else
            return Point2::Zero;
    }

    Point2 GraphicsDevice::GetScreenSize() const
    {
        return GetViewportSize();
    }

    void GraphicsDevice::Initialize()
    {
#       if (defined(BIBIM_USE_EGL))
        BBAssert(GetWindow());

        Window* window = GetWindow();

        EGLNativeDisplayType nativeDisplay = (EGLNativeDisplayType)window->GetDisplayHandle();
        if (nativeDisplay == 0)
            nativeDisplay = EGL_DEFAULT_DISPLAY;

        eglDisplay = eglGetDisplay(nativeDisplay);
        if (eglDisplay == EGL_NO_DISPLAY)
        {
            // "Could not get EGL display"
            // CloseNativeDisplay(nativeDisplay);
            return;
        }


        EGLint major = 0;
        EGLint minor = 0;
        if (!eglInitialize(eglDisplay, &major, &minor))
        {
            // "Could not initialize EGL display"
            // CloseNativeDisplay(nativeDisplay);
            return;
        }
        if (major < 1 || minor < 4)
        {
            // Does not support EGL 1.4
            // "System does not support at least EGL 1.4"
            // CloseNativeDisplay(nativeDisplay);
            return;
        
        }


        // Obtain the first configuration with a depth buffer
        EGLint attrs[] =
        {
            EGL_RED_SIZE,        8,
            EGL_GREEN_SIZE,      8,
            EGL_BLUE_SIZE,       8,
            EGL_ALPHA_SIZE,      8,
            EGL_DEPTH_SIZE,      16,
            EGL_SURFACE_TYPE,    EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE
        };
        EGLint numberOfConfigs = 0;
        EGLConfig eglConfig = 0;
        if (!eglChooseConfig(eglDisplay, attrs, &eglConfig, 1, &numberOfConfigs))
        {
            // "Could not find valid EGL config"
            // CloseNativeDisplay(nativeDisplay);
            return;
        }


        // Get the native visual id
        int nativeVisualID;
        if (!eglGetConfigAttrib(eglDisplay, eglConfig, EGL_NATIVE_VISUAL_ID, &nativeVisualID))
        {
            // "Could not get native visual id"
            // CloseNativeDisplay(nativeDisplay);
            return;
        }

        EGLNativeWindowType nativeWindow = (EGLNativeWindowType)window->GetHandle();
#       if (defined(BIBIM_PLATFORM_WINDOWS))
        if (nativeWindow == 0)
        {
            // "Could not create window"
            // CloseNativeDisplay(nativeDisplay);
            return;
        }
#       endif

        const EGLint contextAttrs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
        eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttrs);
        if (eglContext == EGL_NO_CONTEXT)
        {
            // "Could not create EGL context"
            // DestroyNativeWin(nativeDisplay, nativeWin);
            // CloseNativeDisplay(nativeDisplay);
            return;
        }

        //const EGLint surfaceAttrs[] = { EGL_RENDER_BUFFER, EGL_BACK_BUFFER, EGL_NONE };
        eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, nativeWindow, NULL);
        if (eglSurface == EGL_NO_SURFACE)
        {
            // "Could not create EGL surface"
            // DestroyNativeWin(nativeDisplay, nativeWin);
            // CloseNativeDisplay(nativeDisplay);
            return;
        }

        if(!eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext))
        {
            // "Could not activate EGL context"
            // DestroyNativeWin(nativeDisplay, nativeWin);
            // CloseNativeDisplay(nativeDisplay);
            return;
        }
#       endif

        // capabilities.displayModes;
        capabilities.vertexShaderVersion = GraphicsCapabilities::VS20;
        capabilities.pixelShaderVersion = GraphicsCapabilities::PS20;

        const Point2 windowSize = GetWindow()->GetSize();
        glViewport(0, 0, windowSize.X, windowSize.Y);

        Base::Initialize();
    }

    void GraphicsDevice::Finalize()
    {
        Base::Finalize();

#       if (defined(BIBIM_USE_EGL))
        eglMakeCurrent(EGL_NO_DISPLAY, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (eglDisplay)
        {
            if (eglContext)
                eglDestroyContext(eglDisplay, eglContext);
            if (eglSurface)
                eglDestroySurface(eglDisplay, eglSurface);

            eglTerminate(eglDisplay);
        }
#       endif
    }
}

#endif