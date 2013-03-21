#include <Bibim/PCH.h>
#include <Bibim/ScreenshotPrinter.h>
#include <Bibim/Assert.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/RenderTargetTexture2D.h>
#include <Bibim/Window.h>

namespace Bibim
{
    ScreenshotPrinter::ScreenshotPrinter()
        : graphicsDevice(nullptr)
    {
    }

    ScreenshotPrinter::ScreenshotPrinter(GraphicsDevice* graphicsDevice)
        : graphicsDevice(nullptr)
    {
        SetGraphicsDevice(graphicsDevice);
    }

    ScreenshotPrinter::~ScreenshotPrinter()
    {
    }

    void ScreenshotPrinter::BeginDraw()
    {
#       if (defined(BIBIM_USE_DIRECTX9))
        if (graphicsDevice == nullptr || graphicsDevice->GetWindow() == nullptr)
            return;

        if (renderTarget == nullptr)
        {
            const Point2 resolution = graphicsDevice->GetResolution();
            renderTarget = new RenderTargetTexture2D(graphicsDevice, resolution.X, resolution.Y);
        }

        IDirect3DDevice9*  d3dDevice = graphicsDevice->GetD3DDevice();
        IDirect3DSurface9* d3dSurface = renderTarget->GetD3DSurface();

        d3dDevice->SetRenderTarget(0, d3dSurface);
        d3dDevice->BeginScene();
#       endif
    }

    void ScreenshotPrinter::EndDraw()
    {
#       if (defined(BIBIM_USE_DIRECTX9))
        BBAssert(graphicsDevice && renderTarget);

        IDirect3DDevice9*  d3dDevice = graphicsDevice->GetD3DDevice();
        d3dDevice->EndScene();
        d3dDevice->SetRenderTarget(0, nullptr);
#       endif
    }

    void ScreenshotPrinter::SetGraphicsDevice(GraphicsDevice* value)
    {
        if (graphicsDevice != value)
        {
            if (graphicsDevice)
                renderTarget.Reset();

            graphicsDevice = value;
        }
    }
}