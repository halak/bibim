namespace Bibim
{
    Window* GraphicsDeviceBase::GetWindow() const
    {
        return window;
    }

    void GraphicsDeviceBase::Reset()
    {
        Finalize();
        Initialize();
    }
}