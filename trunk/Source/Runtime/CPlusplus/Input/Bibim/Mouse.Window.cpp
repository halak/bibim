#include <Bibim/Config.h>
#include <Bibim/Mouse.h>
#include <Bibim/Window.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace Bibim
{
    void Mouse::SetPosition(Point2 value)
    {
        POINT windowsMousePosition = { value.X, value.Y };
        ::ClientToScreen(static_cast<HWND>(window->GetHandle()), &windowsMousePosition);
        ::SetCursorPos(windowsMousePosition.x, windowsMousePosition.y);
    }

    void Mouse::SetVisible(bool value)
    {
        if (isVisible != value)
        {
            isVisible = value;
            ::ShowCursor(value ? TRUE : FALSE);

            CURSORINFO cursorInfo = { 0, };
            cursorInfo.cbSize = sizeof(cursorInfo);
            ::GetCursorInfo(&cursorInfo);
            state.IsVisible = cursorInfo.flags != 0;
        }
    }
}