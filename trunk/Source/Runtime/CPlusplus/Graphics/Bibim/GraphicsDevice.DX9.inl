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