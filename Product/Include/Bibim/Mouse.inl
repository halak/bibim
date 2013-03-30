namespace Bibim
{
    const MouseState& Mouse::GetState()
    {
        return state;
    }

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
}