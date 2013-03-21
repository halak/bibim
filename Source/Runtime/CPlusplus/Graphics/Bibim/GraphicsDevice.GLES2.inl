namespace Bibim
{
    bool GraphicsDevice::GetFullscreen() const
    {
        return fullscreen;
    }

    const GraphicsCapabilities& GraphicsDevice::GetCapabilities() const
    {
        return capabilities;
    }
}