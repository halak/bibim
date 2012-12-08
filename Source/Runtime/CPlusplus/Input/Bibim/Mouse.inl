namespace Bibim
{
    void Mouse::Show()
    {
        SetVisible(true);
    }

    void Mouse::Hide()
    {
        SetVisible(false);
    }

    Window* Mouse::GetWindow()
    {
        return window;
    }

    void Mouse::SetWindow(Window* value)
    {
        window = value;
    }
}