#include <Bibim/PCH.h>
#include <Bibim/Mouse.h>
#include <Bibim/MouseState.h>
#include <Bibim/Window.h>

namespace Bibim
{
    Mouse::Mouse()
        : window(nullptr),
          state(new MouseState())
    {
    }

    Mouse::Mouse(Window* window)
        : window(window),
          state(new MouseState())
    {
        if (window)
            window->MouseWheel().Connect(this, &Mouse::OnMouseWheel);
    }

    Mouse::~Mouse()
    {
        SetWindow(nullptr);
        delete state;
    }

    Window* Mouse::GetWindow()
    {
        return window;
    }

    void Mouse::SetWindow(Window* value)
    {
        if (window != value)
        {
            if (window)
                window->MouseWheel().Disconnect(this, &Mouse::OnMouseWheel);

            window = value;

            if (window)
                window->MouseWheel().Connect(this, &Mouse::OnMouseWheel);
        }
    }

    void Mouse::OnMouseWheel(int delta)
    {
        state->Wheel += delta;
    }
}