#include <Bibim/PCH.h>
#include <Bibim/Mouse.h>
#include <Bibim/Window.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>

    namespace Bibim
    {
        const MouseState& Mouse::GetState()
        {
            HWND handle = static_cast<HWND>(window->GetHandle());
            POINT windowsMousePosition = { 0, 0 };
            ::GetCursorPos(&windowsMousePosition);
            ::ScreenToClient(handle, &windowsMousePosition);
            state.Position = Point2(windowsMousePosition.x, windowsMousePosition.y);
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

            state.Wheel = 0;
            return state;
        }

        void Mouse::SetPosition(Point2 value)
        {
            POINT windowsMousePosition = { value.X, value.Y };
            ::ClientToScreen(static_cast<HWND>(window->GetHandle()), &windowsMousePosition);
            ::SetCursorPos(windowsMousePosition.x, windowsMousePosition.y);
        }
    }

#endif