#include <Bibim/PCH.h>
#include <Bibim/GraphicsDevice.GLES2.h>
#include <Bibim/Assert.h>
#include <Bibim/CheckedRelease.h>
#include <Bibim/Colors.h>
#include <Bibim/Exception.h>
#include <Bibim/Log.h>
#include <Bibim/RenderTargetTexture2D.GLES2.h>
#include <Bibim/Window.h>
#include <algorithm>

namespace Bibim
{
    GraphicsDevice::GraphicsDevice()
        : eglDisplay(nullptr),
          eglSurface(nullptr),
          eglContext(nullptr),
          window(nullptr),
          resolution(1024, 768),
          viewport(Rect::Empty),
          fullscreen(false)
    {
    }

    GraphicsDevice::GraphicsDevice(int resolutionWidth, int resolutionHeight)
        : eglDisplay(nullptr),
          eglSurface(nullptr),
          eglContext(nullptr),
          window(nullptr),
          resolution(resolutionWidth, resolutionHeight),
          viewport(Rect::Empty),
          fullscreen(false)
    {
        BBAssert(resolutionWidth > 0 && resolutionHeight > 0);
    }

    GraphicsDevice::~GraphicsDevice()
    {
        FinalizeContext();
    }

    void GraphicsDevice::Clear()
    {
        Clear(Colors::CornflowerBlue);
    }

    void GraphicsDevice::Clear(Color color)
    {
        const Vector4 colorVector = color.ToVector4();
        glClearColor(colorVector.X, colorVector.Y, colorVector.Z, colorVector.W);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GraphicsDevice::BeginDraw()
    {
    }

    void GraphicsDevice::BeginDraw(RenderTargetTexture2D* /*renderTarget*/)
    {
        throw;
    }

    void GraphicsDevice::EndDraw()
    {
    }

    void GraphicsDevice::EndDraw(RenderTargetTexture2D* /*renderTarget*/)
    {
        throw;
    }

    void GraphicsDevice::Present()
    {
        eglSwapBuffers(eglDisplay, eglSurface);
    }

    void GraphicsDevice::SetWindow(Window* value)
    {
        if (GetWindow() != value)
        {
            FinalizeContext();

            window = value;

            if (GetWindow())
                InitializeContext();
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
            glViewport(viewport.X, viewport.Y, viewport.Width, viewport.Height);
        }
    }

    void GraphicsDevice::InitializeContext()
    {
        BBAssert(GetWindow());

        Window* window = GetWindow();

        EGLNativeDisplayType nativeDisplay = static_cast<EGLNativeDisplayType>(window->GetDisplayHandle());
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
        EGLint attrs[] = { EGL_DEPTH_SIZE, 16, EGL_NONE };
        EGLint numberOfConfigs =0;
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


        EGLNativeWindowType nativeWindow = static_cast<EGLNativeWindowType>(window->GetHandle());
        if (nativeWindow == nullptr)
        {
            // "Could not create window"
            // CloseNativeDisplay(nativeDisplay);
            return;
        }


        eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, nativeWindow, NULL);
        if (eglSurface == EGL_NO_SURFACE)
        {
            // "Could not create EGL surface"
            // DestroyNativeWin(nativeDisplay, nativeWin);
            // CloseNativeDisplay(nativeDisplay);
            return;
        }


        eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, NULL);
        if (eglContext == EGL_NO_CONTEXT)
        {
            // "Could not create EGL context"
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


        capabilities.displayModes;
        capabilities.vertexShaderVersion = GraphicsCapabilities::VS20;
        capabilities.pixelShaderVersion = GraphicsCapabilities::PS20;



        /*
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
        d3dParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

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
        */

        SetViewport(Rect(Point2::Zero, resolution));
    }

    void GraphicsDevice::FinalizeContext()
    {
        eglMakeCurrent(EGL_NO_DISPLAY, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (eglDisplay)
        {
            if (eglContext)
                eglDestroyContext(eglDisplay, eglContext);
            if (eglSurface)
                eglDestroySurface(eglDisplay, eglSurface);

            eglTerminate(eglDisplay);
        }
    }
}