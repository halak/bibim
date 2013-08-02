#pragma once
#ifndef __BIBIM_GRAPHICSDEVICE_DX9_H__
#define __BIBIM_GRAPHICSDEVICE_DX9_H__

#include <Bibim/FWD.h>
#if (defined(BIBIM_USE_DIRECTX9))

#include <Bibim/GraphicsDeviceBase.h>
#include <Bibim/Color.h>
#include <Bibim/GraphicsCapabilities.h>
#include <Bibim/Rect.h>
#include <Bibim/Window.h>
#include <list>
#include <vector>
#include <d3d9.h>

namespace Bibim
{
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

            Point2 GetViewportSize() const;
            Point2 GetScreenSize() const;

            inline const GraphicsCapabilities& GetCapabilities() const;

            inline IDirect3D9*       GetD3DObject();
            inline IDirect3DDevice9* GetD3DDevice();
            inline const D3DCAPS9&   GetD3DCaps() const;

        private:
            virtual void Initialize();
            virtual void Finalize();

        private:
            IDirect3D9*       d3dObject;
            IDirect3DDevice9* d3dDevice;
            IDirect3DSurface9* d3dBackbufferSurface;
            D3DCAPS9 d3dCaps;

            GraphicsCapabilities capabilities;

            bool fullscreen;
            bool deviceLost;
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

    IDirect3D9* GraphicsDevice::GetD3DObject()
    {
        return d3dObject;
    }

    IDirect3DDevice9* GraphicsDevice::GetD3DDevice()
    {
        return d3dDevice;
    }

    const D3DCAPS9& GraphicsDevice::GetD3DCaps() const
    {
        return d3dCaps;
    }
}

#endif
#endif