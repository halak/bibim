#include <Bibim/PCH.h>
#include <Bibim/DisplaySwapChain.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Window.h>
#include <d3dx9.h>

namespace Bibim
{
    DisplaySwapChain::DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window)
        : graphicsDevice(graphicsDevice),
          window(window),
          backbufferSize(Point::Zero),
          viewport(Rect::Empty),
          swapChain(nullptr),
          backBuffer(nullptr)
    {
        BBAssertDebug(window);
        Construct(window, window->GetSize());
    }

    DisplaySwapChain::DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window, Point size)
         : graphicsDevice(graphicsDevice),
           window(window),
           backbufferSize(Point::Zero),
           viewport(Rect::Empty),
           swapChain(nullptr),
           backBuffer(nullptr)
    {
        BBAssertDebug(size.X > 0 && size.Y > 0);
        Construct(window, size);
    }

    DisplaySwapChain::DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window, void* swapChainInterface)
         : graphicsDevice(graphicsDevice),
           window(window),
           backbufferSize(Point::Zero),
           viewport(Rect::Empty),
           swapChain(nullptr),
           backBuffer(nullptr)
    {
        // GraphicsDevice에서 생성하므로 알아서 추가합니다.

        swapChain = static_cast<IDirect3DSwapChain9*>(swapChainInterface);

        HRESULT result = D3D_OK;
        
        result = swapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
        if (result != D3D_OK)
            return;

        SetViewport(Rect(0, 0, window->GetSize().X, window->GetSize().Y));
    }

    DisplaySwapChain::~DisplaySwapChain()
    {
        CheckedRelease(backBuffer);
        CheckedRelease(swapChain);
        graphicsDevice->Remove(this);
    }

    void DisplaySwapChain::Construct(Window* window, Point size)
    {
        graphicsDevice->Add(this);

        IDirect3DDevice9* d3dDevice = graphicsDevice->GetD3DDevice();
        if (d3dDevice == nullptr)
            return;

        D3DPRESENT_PARAMETERS d3dParameters;
        d3dParameters.BackBufferWidth = size.X;
        d3dParameters.BackBufferHeight = size.Y;
        d3dParameters.BackBufferFormat = D3DFMT_UNKNOWN;
        d3dParameters.BackBufferCount = 1;
        d3dParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
        d3dParameters.MultiSampleQuality = 0;
        d3dParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dParameters.hDeviceWindow = static_cast<HWND>(window->GetHandle());
        d3dParameters.Windowed = TRUE;
        d3dParameters.EnableAutoDepthStencil = FALSE;
        d3dParameters.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
        d3dParameters.Flags = 0x00000000;
        d3dParameters.FullScreen_RefreshRateInHz = 0;
        d3dParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

        HRESULT result = D3D_OK;

        result = d3dDevice->CreateAdditionalSwapChain(&d3dParameters, &swapChain);
        if (result != D3D_OK)
            return;

        result = swapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
        if (result != D3D_OK)
            return;

        backbufferSize = size;
        SetViewport(Rect(0, 0, size.X, size.Y));
    }

    void DisplaySwapChain::BeginDraw()
    {
        graphicsDevice->SetViewport(viewport);
        graphicsDevice->GetD3DDevice()->SetRenderTarget(0, backBuffer);
        graphicsDevice->GetD3DDevice()->BeginScene();
    }

    void DisplaySwapChain::EndDraw()
    {
        graphicsDevice->GetD3DDevice()->EndScene();
    }

    void DisplaySwapChain::Present()
    {
        swapChain->Present(nullptr, nullptr, static_cast<HWND>(window->GetHandle()), nullptr, 0x00000000);
        backBuffer->Release();
    }
}