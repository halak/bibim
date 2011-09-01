#include <Bibim/PCH.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Assert.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/Colors.h>
#include <Bibim/DisplaySwapChain.h>
#include <Bibim/Window.h>
#include <stdexcept>

namespace Bibim
{
    GraphicsDevice::GraphicsDevice()
        : d3dObject(nullptr),
          d3dDevice(nullptr),
          window(nullptr),
          defaultSwapChain(nullptr),
          viewport(Rectangle::Empty),
          fullscreen(false)
    {
    }

    GraphicsDevice::~GraphicsDevice()
    {
        FinalizeDevice();
        CheckedRelease(d3dObject);
    }

    void GraphicsDevice::Clear()
    {
        Clear(Colors::CornflowerBlue);
    }

    void GraphicsDevice::Clear(Color color)
    {
        GetD3DDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(color.R, color.G, color.B), 1.0f, 0);
    }

    void GraphicsDevice::BeginDraw()
    {
        if (defaultSwapChain == nullptr)
            GetD3DDevice()->BeginScene();
        else
            defaultSwapChain->BeginDraw();
    }

    void GraphicsDevice::EndDraw()
    {
        if (defaultSwapChain == nullptr)
            GetD3DDevice()->EndScene();
        else
            defaultSwapChain->EndDraw();
    }

    void GraphicsDevice::Present()
    {
        if (defaultSwapChain == nullptr)
            GetD3DDevice()->Present(NULL, NULL, NULL, NULL);
        else
            defaultSwapChain->Present();
    }

    Window* GraphicsDevice::GetWindow() const
    {
        return window;
    }

    void GraphicsDevice::SetWindow(Window* value)
    {
        if (GetWindow() != value)
        {
            FinalizeDevice();

            window = value;

            if (GetWindow())
                InitializeDevice();
        }
    }

    bool GraphicsDevice::GetFullscreen() const
    {
        return fullscreen;
    }

    void GraphicsDevice::SetFullscreen(bool value)
    {
        if (GetFullscreen() != value)
        {
            fullscreen = value;
            // Reinitialize Device
        }
    }

    const Rectangle& GraphicsDevice::GetViewport() const
    {
        return viewport;
    }

    void GraphicsDevice::SetViewport(const Rectangle& value)
    {
        if (GetViewport() != value)
        {
            viewport = value;

            const D3DVIEWPORT9 vp = 
            {
                value.X,      // X
                value.Y,      // Y
                value.Width,  // Width
                value.Height, // Height
                0.0f,         // MinZ
                1.0f,         // MaxZ
            };

            HRESULT result = d3dDevice->SetViewport(&vp);
            if (result != D3D_OK)
                throw new std::runtime_error("d3dDevice->SetViewport != D3D_OK");
        }
    }

    DisplaySwapChain* GraphicsDevice::GetDefaultSwapChain()
    {
        if (defaultSwapChain == nullptr)
            AcquireDefaultSwapChain();

        return defaultSwapChain;
    }

    IDirect3D9* GraphicsDevice::GetD3DObject()
    {
        return d3dObject;
    }

    IDirect3DDevice9* GraphicsDevice::GetD3DDevice()
    {
        return d3dDevice;
    }

    void GraphicsDevice::InitializeDevice()
    {
        BBAssert(GetWindow());

        if (d3dObject == NULL)
        {
            d3dObject = Direct3DCreate9(D3D_SDK_VERSION);

            if (d3dObject == NULL)
                throw new std::runtime_error("GraphicsDevice::d3dObject == NULL");
        }

        D3DPRESENT_PARAMETERS d3dParameters;
        d3dParameters.BackBufferWidth = GetWindow()->GetSize().X;
        d3dParameters.BackBufferHeight = GetWindow()->GetSize().Y;
        d3dParameters.BackBufferFormat = D3DFMT_UNKNOWN;
        d3dParameters.BackBufferCount = 1;
        d3dParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
        d3dParameters.MultiSampleQuality = 0;
        d3dParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dParameters.hDeviceWindow = static_cast<HWND>(GetWindow()->GetHandle());
        d3dParameters.Windowed = GetFullscreen() ? FALSE : TRUE;
        d3dParameters.EnableAutoDepthStencil = FALSE;
        d3dParameters.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
        d3dParameters.Flags = 0x00000000;
        d3dParameters.FullScreen_RefreshRateInHz = 0;
        d3dParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

        HRESULT result = D3D_OK;

        result = GetD3DObject()->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dParameters.hDeviceWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dParameters, &d3dDevice);
        if (result != D3D_OK)
            throw new std::runtime_error("d3dObject->CreateDevice != D3D_OK");

        SetViewport(Rectangle(Point::Zero, GetWindow()->GetSize()));
    }

    void GraphicsDevice::FinalizeDevice()
    {
        delete defaultSwapChain;
        defaultSwapChain = nullptr;
        CheckedRelease(d3dDevice);
    }

    void GraphicsDevice::AcquireDefaultSwapChain()
    {
        BBAssertDebug(defaultSwapChain == nullptr);
        BBAssertDebug(swapChains.empty());

        IDirect3DSwapChain9* d3dSwapChain = nullptr;
        HRESULT result = D3D_OK;
        result = GetD3DDevice()->GetSwapChain(0, &d3dSwapChain);
        if (result != D3D_OK)
            throw new std::runtime_error("d3dDevice->GetSwapChain != D3D_OK");

        defaultSwapChain = new DisplaySwapChain(this, window, d3dSwapChain);
        swapChains.push_back(defaultSwapChain);
    }

    void GraphicsDevice::Add(DisplaySwapChain* item)
    {
        if (defaultSwapChain == nullptr)
            AcquireDefaultSwapChain();

        BBAssertDebug(std::find(swapChains.begin(), swapChains.end(), item) == swapChains.end());
        swapChains.push_back(item);
    }

    void GraphicsDevice::Remove(DisplaySwapChain* item)
    {
        std::vector<DisplaySwapChain*>::iterator it = std::find(swapChains.begin(), swapChains.end(), item);
        BBAssertDebug(it != swapChains.end());
        swapChains.erase(it);
    }
}