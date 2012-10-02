﻿#include <Bibim/PCH.h>
#include <Bibim/GraphicsDevice.DX9.h>
#include <Bibim/Assert.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/Colors.h>
#include <Bibim/Exception.h>
#include <Bibim/Log.h>
#include <Bibim/RenderTargetTexture2D.h>
#include <Bibim/Window.h>
#include <algorithm>

namespace Bibim
{
    GraphicsDevice::GraphicsDevice()
        : d3dObject(nullptr),
          d3dDevice(nullptr),
          d3dBackbufferSurface(nullptr),
          window(nullptr),
          resolution(1024, 768),
          defaultSwapChain(nullptr),
          viewport(Rect::Empty),
          fullscreen(false)
    {
        ::ZeroMemory(&d3dCaps, sizeof(d3dCaps));
    }

    GraphicsDevice::GraphicsDevice(int resolutionWidth, int resolutionHeight)
        : d3dObject(nullptr),
          d3dDevice(nullptr),
          d3dBackbufferSurface(nullptr),
          window(nullptr),
          resolution(resolutionWidth, resolutionHeight),
          defaultSwapChain(nullptr),
          viewport(Rect::Empty),
          fullscreen(false)
    {
        BBAssert(resolutionWidth > 0 && resolutionHeight > 0);
        ::ZeroMemory(&d3dCaps, sizeof(d3dCaps));
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
        GetD3DDevice()->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(color.R, color.G, color.B), 1.0f, 0);
    }

    void GraphicsDevice::BeginDraw()
    {
        GetD3DDevice()->BeginScene();
    }

    void GraphicsDevice::BeginDraw(RenderTargetTexture2D* renderTarget)
    {
        BBAssertDebug(renderTarget);

        GetD3DDevice()->GetRenderTarget(0, &d3dBackbufferSurface);

        GetD3DDevice()->SetRenderTarget(0, renderTarget->GetD3DSurface());
        GetD3DDevice()->BeginScene();
    }

    void GraphicsDevice::EndDraw()
    {
        GetD3DDevice()->EndScene();
    }

    void GraphicsDevice::EndDraw(RenderTargetTexture2D* /*renderTarget*/)
    {
        GetD3DDevice()->EndScene();
        GetD3DDevice()->SetRenderTarget(0, d3dBackbufferSurface);
        CheckedRelease(d3dBackbufferSurface);
    }

    void GraphicsDevice::Present()
    {
        GetD3DDevice()->Present(nullptr, nullptr, nullptr, nullptr);
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

    void GraphicsDevice::SetFullscreen(bool value)
    {
        if (GetFullscreen() != value)
        {
            fullscreen = value;

            // TODO: Reinitialize Device
        }
    }

    void GraphicsDevice::SetViewport(const Rect& value)
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
                throw Exception("d3dDevice->SetViewport != D3D_OK");
        }
    }

    void GraphicsDevice::InitializeDevice()
    {
        BBAssert(GetWindow());

        if (d3dObject == nullptr)
        {
            d3dObject = Direct3DCreate9(D3D_SDK_VERSION);
            if (d3dObject == nullptr)
                throw Exception("GraphicsDevice::d3dObject == nullptr");

            struct CollectDisplayModes
            {
                static void Do(DisplayModeCollection& modes, IDirect3D9* d3dObject, D3DFORMAT format, int bitsPerPixel)
                {
                    D3DDISPLAYMODE item = { 0, };
                    const int count = d3dObject->GetAdapterModeCount(D3DADAPTER_DEFAULT, format);
                    modes.reserve(modes.size() + count);
                    for (int i = 0; i < count; i++)
                    {
                        if (d3dObject->EnumAdapterModes(D3DADAPTER_DEFAULT, format, i, &item) == D3D_OK)
                        {
                            BBAssert(item.Format == format);
                            modes.push_back(DisplayMode(static_cast<int>(item.Width),
                                                        static_cast<int>(item.Height),
                                                        static_cast<int>(item.RefreshRate),
                                                        bitsPerPixel));
                        }
                    }
                }
            };

            DisplayModeCollection modes;
            CollectDisplayModes::Do(modes, d3dObject, D3DFMT_A1R5G5B5, 16);
            CollectDisplayModes::Do(modes, d3dObject, D3DFMT_A2R10G10B10, 32);
            CollectDisplayModes::Do(modes, d3dObject, D3DFMT_A8R8G8B8, 32);
            CollectDisplayModes::Do(modes, d3dObject, D3DFMT_R5G6B5, 16);
            CollectDisplayModes::Do(modes, d3dObject, D3DFMT_X1R5G5B5, 16);
            CollectDisplayModes::Do(modes, d3dObject, D3DFMT_X8R8G8B8, 32);
            capabilities.displayModes.swap(modes);
        }

        D3DPRESENT_PARAMETERS d3dParameters;
        d3dParameters.BackBufferWidth = resolution.X;
        d3dParameters.BackBufferHeight = resolution.Y;
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

        result = GetD3DObject()->CreateDevice(D3DADAPTER_DEFAULT,
                                              D3DDEVTYPE_HAL,
                                              d3dParameters.hDeviceWindow,
                                              D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                              &d3dParameters,
                                              &d3dDevice);
        if (result != D3D_OK)
        {
            result = GetD3DObject()->CreateDevice(D3DADAPTER_DEFAULT,
                                                  D3DDEVTYPE_HAL,
                                                  d3dParameters.hDeviceWindow,
                                                  D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                                  &d3dParameters,
                                                  &d3dDevice);
            if (result == D3D_OK)
                Log::Information("Graphics", "device created by Software vertex processing.");
            else
                throw Exception("d3dObject->CreateDevice != D3D_OK");
        }

        if (d3dDevice->GetDeviceCaps(&d3dCaps) == D3D_OK)
        {
            const int vsMajor = D3DSHADER_VERSION_MAJOR(d3dCaps.VertexShaderVersion);
            const int vsMinor = D3DSHADER_VERSION_MINOR(d3dCaps.VertexShaderVersion);
            const int psMajor = D3DSHADER_VERSION_MAJOR(d3dCaps.PixelShaderVersion);
            const int psMinor = D3DSHADER_VERSION_MINOR(d3dCaps.PixelShaderVersion);

            switch (vsMajor)
            {
                case 0:
                    capabilities.vertexShaderVersion = GraphicsCapabilities::VSNotSupported;
                    break;
                case 1:
                    if (vsMinor >= 1)
                        capabilities.vertexShaderVersion = GraphicsCapabilities::VS1x;
                    else
                        capabilities.vertexShaderVersion = GraphicsCapabilities::VSNotSupported;
                    break;
                case 2:
                    if (vsMinor == 0)
                        capabilities.vertexShaderVersion = GraphicsCapabilities::VS20;
                    else
                        capabilities.vertexShaderVersion = GraphicsCapabilities::VS2x;
                    break;
                case 3:
                    capabilities.vertexShaderVersion = GraphicsCapabilities::VS30;
                    break;
                case 4:
                    capabilities.vertexShaderVersion = GraphicsCapabilities::VS40;
                    break;
                default:
                    capabilities.vertexShaderVersion = GraphicsCapabilities::VSUpperVersion;
                    break;
            }

            switch (psMajor)
            {
                case 0:
                    capabilities.pixelShaderVersion = GraphicsCapabilities::PSNotSupported;
                    break;
                case 1:
                    if (psMinor >= 1)
                        capabilities.pixelShaderVersion = GraphicsCapabilities::PS1x;
                    else
                        capabilities.pixelShaderVersion = GraphicsCapabilities::PSNotSupported;
                    break;
                case 2:
                    if (psMinor == 0)
                        capabilities.pixelShaderVersion = GraphicsCapabilities::PS20;
                    else
                        capabilities.pixelShaderVersion = GraphicsCapabilities::PS2x;
                    break;
                case 3:
                    capabilities.pixelShaderVersion = GraphicsCapabilities::PS30;
                    break;
                case 4:
                    capabilities.pixelShaderVersion = GraphicsCapabilities::PS40;
                    break;
                default:
                    capabilities.pixelShaderVersion = GraphicsCapabilities::PSUpperVersion;
                    break;
            }

            // capabilities.vertexShaderVersion = GraphicsCapabilities::VSNotSupported;
            // capabilities.pixelShaderVersion  = GraphicsCapabilities::PSNotSupported;

            if ((d3dCaps.Caps2 & D3DCAPS2_DYNAMICTEXTURES) == 0x00000000)
                Log::Warning("Graphics", "This videocard is dynamic texture not supported.");

            BBAssert(d3dCaps.PrimitiveMiscCaps & D3DPMISCCAPS_CULLNONE);
            BBAssert(d3dCaps.ZCmpCaps & D3DPCMPCAPS_ALWAYS);
            BBAssert(d3dCaps.SrcBlendCaps);
            BBAssert(d3dCaps.DestBlendCaps);
            BBAssert(d3dCaps.TextureCaps & D3DPTEXTURECAPS_ALPHA);
            BBAssert((d3dCaps.TextureCaps & D3DPTEXTURECAPS_SQUAREONLY) == 0x00000000);
            BBAssert(d3dCaps.MaxTextureWidth >= 1024);
            BBAssert(d3dCaps.MaxTextureHeight >= 1024);
            BBAssert(d3dCaps.TextureOpCaps & D3DTEXOPCAPS_ADD);
            BBAssert(d3dCaps.TextureOpCaps & D3DTEXOPCAPS_ADDSIGNED);
            BBAssert(d3dCaps.TextureOpCaps & D3DTEXOPCAPS_ADDSIGNED2X);
            BBAssert(d3dCaps.TextureOpCaps & D3DTEXOPCAPS_DISABLE);
            BBAssert(d3dCaps.TextureOpCaps & D3DTEXOPCAPS_MODULATE);
            BBAssert(d3dCaps.TextureOpCaps & D3DTEXOPCAPS_MODULATE2X);
            BBAssert(d3dCaps.TextureOpCaps & D3DTEXOPCAPS_MODULATE4X);
            BBAssert(d3dCaps.TextureOpCaps & D3DTEXOPCAPS_SELECTARG1);
            BBAssert(d3dCaps.TextureOpCaps & D3DTEXOPCAPS_SELECTARG2);
            BBAssert(d3dCaps.TextureOpCaps & D3DTEXOPCAPS_SUBTRACT);
            BBAssert(d3dCaps.MaxTextureBlendStages >= 4);
            BBAssert(d3dCaps.MaxSimultaneousTextures >= 2);
        }

        SetViewport(Rect(Point2::Zero, resolution));
    }

    void GraphicsDevice::FinalizeDevice()
    {
        capabilities = GraphicsCapabilities();
        ::ZeroMemory(&d3dCaps, sizeof(d3dCaps));
        CheckedRelease(d3dDevice);
    }
}