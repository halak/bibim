#pragma once
#ifndef __BIBIM_GRAPHICSDEVICE_DX9_H__
#define __BIBIM_GRAPHICSDEVICE_DX9_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Color.h>
#   include <Bibim/GraphicsCapabilities.h>
#   include <Bibim/Rect.h>
#   include <Bibim/GLES2.h>
#   include <vector>

    namespace Bibim
    {
        class GraphicsDevice : public GameModule
        {
            BBModuleClass(GraphicsDevice, GameModule, 'G', 'R', 'P', 'D');
            public:
                GraphicsDevice();
                GraphicsDevice(int resolutionWidth, int resolutionHeight);
                virtual ~GraphicsDevice();

                void Clear();
                void Clear(Color color);

                void BeginDraw();
                void BeginDraw(RenderTargetTexture2D* renderTarget);
                void EndDraw();
                void EndDraw(RenderTargetTexture2D* renderTarget);
                void Present();

                inline Window* GetWindow() const;
                void SetWindow(Window* value);

                inline bool GetFullscreen() const;
                void SetFullscreen(bool value);

                inline const Rect& GetViewport() const;
                void SetViewport(const Rect& value);

                inline Point2 GetResolution() const;

                inline const GraphicsCapabilities& GetCapabilities() const;

            private:
                void Construct(int width, int height);
                void InitializeContext();
                void FinalizeContext();

            private:
#               if (defined(BIBIM_PLATFORM_WINDOWS))
                EGLDisplay eglDisplay;
                EGLSurface eglSurface;
                EGLContext eglContext;
#               endif

                Window* window;
                Point2 resolution;

                GraphicsCapabilities capabilities;

                Rect viewport;
                bool fullscreen;
        };
    }

#   include <Bibim/GraphicsDevice.GLES2.inl>

#endif