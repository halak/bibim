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

    Point2 GraphicsDevice::GetResolution() const
    {
        return resolution;
    }

    const GraphicsCapabilities& GraphicsDevice::GetCapabilities() const
    {
        return capabilities;
    }
}