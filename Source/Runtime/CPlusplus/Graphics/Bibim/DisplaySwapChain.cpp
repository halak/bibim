#include <Bibim/PCH.h>
#include <Bibim/DisplaySwapChain.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Window.h>
#include <d3dx9.h>

namespace Bibim
{
    struct DisplaySwapChain::Fields
    {
        GraphicsDevice* graphicsDevice;
        Window* window;
        Point backbufferSize;
        Rectangle viewport;

        IDirect3DSwapChain9* swapChain;
        IDirect3DSurface9* backBuffer;

        Fields(GraphicsDevice* graphicsDevice, Window* window)
            : graphicsDevice(graphicsDevice),
              window(window),
              backbufferSize(Point::Zero),
              viewport(Rectangle::Empty),
              swapChain(nullptr),
              backBuffer(nullptr)
        {
        }
    };

    DisplaySwapChain::DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window)
        : mPointer(new Fields(graphicsDevice, window)),
          m(*mPointer)
    {
        BBAssertDebug(window);
        Construct(window, window->GetSize());
    }

    DisplaySwapChain::DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window, Point size)
        : mPointer(new Fields(graphicsDevice, window)),
          m(*mPointer)
    {
        BBAssertDebug(size.X > 0 && size.Y > 0);
        Construct(window, size);
    }

    DisplaySwapChain::DisplaySwapChain(GraphicsDevice* graphicsDevice, Window* window, void* swapChainInterface)
        : mPointer(new Fields(graphicsDevice, window)),
          m(*mPointer)
    {
        // GraphicsDevice에서 생성하므로 알아서 추가합니다.

        m.swapChain = static_cast<IDirect3DSwapChain9*>(swapChainInterface);

        HRESULT result = D3D_OK;
        
        result = m.swapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &m.backBuffer);
        if (result != D3D_OK)
            return;

        SetViewport(Rectangle(0, 0, window->GetSize().X, window->GetSize().Y));
    }

    DisplaySwapChain::~DisplaySwapChain()
    {
        CheckedRelease(m.backBuffer);
        CheckedRelease(m.swapChain);
        m.graphicsDevice->Remove(this);
        delete mPointer;
    }

    void DisplaySwapChain::Construct(Window* window, Point size)
    {
        m.graphicsDevice->Add(this);

        IDirect3DDevice9* d3dDevice = m.graphicsDevice->GetD3DDevice();
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

        result = d3dDevice->CreateAdditionalSwapChain(&d3dParameters, &m.swapChain);
        if (result != D3D_OK)
            return;

        result = m.swapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &m.backBuffer);
        if (result != D3D_OK)
            return;

        m.backbufferSize = size;
        SetViewport(Rectangle(0, 0, size.X, size.Y));
    }

    void DisplaySwapChain::BeginDraw()
    {
        m.graphicsDevice->SetViewport(m.viewport);
        m.graphicsDevice->GetD3DDevice()->SetRenderTarget(0, m.backBuffer);
        m.graphicsDevice->GetD3DDevice()->BeginScene();
    }

    void DisplaySwapChain::EndDraw()
    {
        m.graphicsDevice->GetD3DDevice()->EndScene();
    }

    void DisplaySwapChain::Present()
    {
        m.swapChain->Present(NULL, NULL, static_cast<HWND>(m.window->GetHandle()), NULL, 0x00000000);
        m.backBuffer->Release();
    }

    GraphicsDevice* DisplaySwapChain::GetGraphicsDevice() const
    {
        return m.graphicsDevice;
    }

    Window* DisplaySwapChain::GetWindow() const
    {
        return m.window;
    }

    Point DisplaySwapChain::GetBackbufferSize() const
    {
        return m.backbufferSize;
    }

    const Rectangle& DisplaySwapChain::GetViewport() const
    {
        return m.viewport;
    }

    void DisplaySwapChain::SetViewport(const Rectangle& value)
    {
        m.viewport = value;
    }
}