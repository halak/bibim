#pragma once
#ifndef __BIBIM_GRAPHICSDEVICE_GLES2_H__
#define __BIBIM_GRAPHICSDEVICE_GLES2_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_USE_OPENGLES2))

#include <Bibim/GraphicsDeviceBase.h>
#include <Bibim/Color.h>
#include <Bibim/GraphicsCapabilities.h>
#include <Bibim/Rect.h>
#include <Bibim/Window.h>
#include <vector>

namespace Bibim
{
#   if (defined(BIBIM_PLATFORM_WINDOWS))
#       define BIBIM_USE_EGL
#   endif

    class GraphicsDevice : public GraphicsDeviceBase
    {
        BBModuleClass(GraphicsDevice, GraphicsDeviceBase, 'G', 'R', 'P', 'D');
        public:
            GraphicsDevice();
            virtual ~GraphicsDevice();

            void Clear();
            void Clear(Color color);

            bool BeginDraw();
            bool BeginDraw(RenderTargetTexture2D* renderTarget);
            void EndDraw();
            void EndDraw(RenderTargetTexture2D* renderTarget);
            void Present();

            inline bool GetFullscreen() const;
            void SetFullscreen(bool value);

            void SetScissorRect();
            void SetScissorRect(Rect value);

            Point2 GetViewportSize() const;
            Point2 GetScreenSize() const;

            inline const GraphicsCapabilities& GetCapabilities() const;

        private:
            virtual void Initialize();
            virtual void Finalize();

        private:
#           if (defined(BIBIM_USE_EGL))
            void* eglDisplay;
            void* eglSurface;
            void* eglContext;
#           endif

            GraphicsCapabilities capabilities;

            bool fullscreen;
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    bool GraphicsDevice::GetFullscreen() const
    {
        return fullscreen;
    }

    const GraphicsCapabilities& GraphicsDevice::GetCapabilities() const
    {
        return capabilities;
    }
}

#endif
#endif