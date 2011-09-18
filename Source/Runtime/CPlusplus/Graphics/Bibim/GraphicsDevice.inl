namespace Bibim
{
    Window* GraphicsDevice::GetWindow() const
    {
        return window;
    }

    bool GraphicsDevice::GetFullscreen() const
    {
        return fullscreen;
    }

    const Rect& GraphicsDevice::GetViewport() const
    {
        return viewport;
    }

    IDirect3D9* GraphicsDevice::GetD3DObject()
    {
        return d3dObject;
    }

    IDirect3DDevice9* GraphicsDevice::GetD3DDevice()
    {
        return d3dDevice;
    }
}