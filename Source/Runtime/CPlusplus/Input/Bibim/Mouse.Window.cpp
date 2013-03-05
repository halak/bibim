#include <Bibim/PCH.h>
#include <Bibim/Mouse.h>
#include <Bibim/Window.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#   endif
#   include <windows.h>

    namespace Bibim
    {
        const MouseState& Mouse::GetState()
        {
            HWND handle = static_cast<HWND>(window->GetHandle());
            CURSORINFO cursorInfo = { 0, };
            cursorInfo.cbSize = sizeof(cursorInfo);
            ::GetCursorInfo(&cursorInfo);
            ::ScreenToClient(handle, &cursorInfo.ptScreenPos);
            state.Position = Point2(cursorInfo.ptScreenPos.x, cursorInfo.ptScreenPos.y);
            state.Wheel = 0;
            if (::GetForegroundWindow() == handle)
            {
                state.IsLeftButtonPressed   = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0x0000;
                state.IsRightButtonPressed  = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0x0000;
                state.IsMiddleButtonPressed = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0x0000;
            }
            else
            {
                state.IsLeftButtonPressed   = false;
                state.IsRightButtonPressed  = false;
                state.IsMiddleButtonPressed = false;
            }
            state.IsVisible = cursorInfo.flags != 0;
            return state;
        }

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
            }
        }
    }

#endif