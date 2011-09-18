namespace Bibim
{
    GraphicsDevice* DisplaySwapChain::GetGraphicsDevice() const
    {
        return graphicsDevice;
    }

    Window* DisplaySwapChain::GetWindow() const
    {
        return window;
    }

    Point DisplaySwapChain::GetBackbufferSize() const
    {
        return backbufferSize;
    }

    const Rect& DisplaySwapChain::GetViewport() const
    {
        return viewport;
    }

    void DisplaySwapChain::SetViewport(const Rect& value)
    {
        viewport = value;
    }
}