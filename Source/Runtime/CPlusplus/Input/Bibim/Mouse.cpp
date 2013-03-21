#include <Bibim/PCH.h>
#include <Bibim/Mouse.h>
#include <Bibim/Window.h>

namespace Bibim
{
    Mouse::Mouse()
        : window(nullptr),
          isVisible(true)
    {
    }

    Mouse::Mouse(Window* window)
        : window(nullptr),
          isVisible(true)
    {
        SetWindow(window);
    }

    Mouse::~Mouse()
    {
        SetWindow(nullptr);
    }

    void Mouse::SetWindow(Window* value)
    {
        if (window != value)
        {
            if (window)
                window->RemoveMouseEventListener(this);

            window = value;

            if (window)
                window->AddMouseEventListener(this);
        }
    }

    void Mouse::OnMouseMove(Window* /*window*/, int x, int y)
    {
        state.Position = Point2(x, y);
    }

    void Mouse::OnMouseLeftButtonDown(Window* /*window*/, int x, int y)
    {
        state.Position = Point2(x, y);
        state.IsLeftButtonPressed = true;
    }

    void Mouse::OnMouseLeftButtonUp(Window* /*window*/, int x, int y)
    {
        state.Position = Point2(x, y);
        state.IsLeftButtonPressed = false;
    }

    void Mouse::OnMouseMiddleButtonDown(Window* /*window*/, int x, int y)
    {
        state.Position = Point2(x, y);
        state.IsMiddleButtonPressed = true;
    }

    void Mouse::OnMouseMiddleButtonUp(Window* /*window*/, int x, int y)
    {
        state.Position = Point2(x, y);
        state.IsMiddleButtonPressed = false;
    }

    void Mouse::OnMouseRightButtonDown(Window* /*window*/, int x, int y)
    {
        state.Position = Point2(x, y);
        state.IsRightButtonPressed = true;
    }

    void Mouse::OnMouseRightButtonUp(Window* /*window*/, int x, int y)
    {
        state.Position = Point2(x, y);
        state.IsRightButtonPressed = false;
    }

    void Mouse::OnMouseWheel(Window* /*window*/, int value)
    {
        state.Wheel = value;
    }
}