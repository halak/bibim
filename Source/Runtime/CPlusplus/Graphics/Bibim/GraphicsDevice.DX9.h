#pragma once
#ifndef __BIBIM_GRAPHICSDEVICE_DX9_H__
#define __BIBIM_GRAPHICSDEVICE_DX9_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameModule.h>
#   include <Bibim/Color.h>
#   include <Bibim/GraphicsCapabilities.h>
#   include <Bibim/Rect.h>
#   include <vector>
#   include <d3d9.h>

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

                DisplaySwapChain* GetDefaultSwapChain();

                inline IDirect3D9*       GetD3DObject();
                inline IDirect3DDevice9* GetD3DDevice();
                inline const D3DCAPS9&   GetD3DCaps() const;

            private:
                void InitializeDevice();
                void FinalizeDevice();

                void AcquireDefaultSwapChain();

                void Add(DisplaySwapChain* item);
                void Remove(DisplaySwapChain* item);

            private:
                IDirect3D9*       d3dObject;
                IDirect3DDevice9* d3dDevice;
                IDirect3DSurface9* d3dBackbufferSurface;
                D3DCAPS9 d3dCaps;
                Window* window;
                Point2 resolution;

                GraphicsCapabilities capabilities;
                DisplaySwapChain* defaultSwapChain;
                std::vector<DisplaySwapChain*> swapChains;

                Rect viewport;
                bool fullscreen;

                friend class DisplaySwapChain;
        };
    }

#   include <Bibim/GraphicsDevice.DX9.inl>

#endif