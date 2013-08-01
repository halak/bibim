#include <Bibim/Config.h>
#include <Bibim/GameWindow.Windows.h>
#include <Bibim/Log.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>

namespace Bibim
{
    static const char* ClassName = "Halak.Bibim.GameWindow";

    struct GameWindow::Internal
    {
        static LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
    };

    GameWindow::GameWindow()
        : handle(nullptr),
          visible(false),
          isUserSizing(false)
    {
    }

    GameWindow::~GameWindow()
    {
        Close();
    }

    void GameWindow::MoveToScreenCenter()
    {
        if (handle == nullptr)
            CreateHandle();

        RECT windowRect = { 0, 0, 0, 0 };
        if (::GetWindowRect(static_cast<HWND>(handle), &windowRect))
        {
            const SIZE screenSize = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
            const SIZE windowSize = { windowRect.right - windowRect.left, windowRect.bottom - windowRect.top };
            const POINT windowPosition = { (screenSize.cx - windowSize.cx) / 2, (screenSize.cy - windowSize.cy) / 2 };

            SetPosition(Point2(windowPosition.x, windowPosition.y));
        }
    }

    void GameWindow::Close()
    {
        if (handle == nullptr)
            return;

        DestroyWindow(static_cast<HWND>(handle));
    }

    const String& GameWindow::GetTitle() const
    {
        return title;
    }

    void GameWindow::SetTitle(const String& value)
    {
        if (handle == nullptr)
            CreateHandle();

        if (title != value)
        {
            title = value;

            std::vector<wchar_t> wideCharacters;
            wideCharacters.resize(MultiByteToWideChar(CP_UTF8, 0, title.CStr(), title.GetLength(), nullptr, 0) + 1, L'\0');
            MultiByteToWideChar(CP_UTF8, 0, title.CStr(), title.GetLength(), &wideCharacters[0], wideCharacters.size());
            
            ::SetWindowTextW(static_cast<HWND>(handle), &wideCharacters[0]);
        }
    }

    Point2 GameWindow::GetPosition() const
    {
        return position;
    }

    void GameWindow::SetPosition(Point2 value)
    {
        if (handle == nullptr)
            CreateHandle();

        if (position != value)
        {
            position = value;
            
            ::SetWindowPos(static_cast<HWND>(handle), nullptr, position.X, position.Y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
        }
    }

    Point2 GameWindow::GetSize() const
    {
        return size;
    }

    void GameWindow::SetSize(Point2 value)
    {
        if (handle == nullptr)
            CreateHandle();

        if (GetSize() != value)
        {
            size = value;

            const DWORD exWindowStyle = static_cast<DWORD>(GetWindowLong(static_cast<HWND>(handle), GWL_EXSTYLE));
            const DWORD windowStyle = static_cast<DWORD>(GetWindowLong(static_cast<HWND>(handle), GWL_STYLE));
            const BOOL hasMenu = GetMenu(static_cast<HWND>(handle)) != nullptr ? TRUE : FALSE;
            RECT windowRect = { 0, 0, size.X, size.Y };
            ::AdjustWindowRectEx(&windowRect, windowStyle, hasMenu, exWindowStyle);

            const SIZE windowSize = { windowRect.right - windowRect.left, windowRect.bottom - windowRect.top };
            ::SetWindowPos(static_cast<HWND>(handle), nullptr, 0, 0, windowSize.cx, windowSize.cy, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
        }
    }

    bool GameWindow::GetVisible() const
    {
        return visible;
    }

    void GameWindow::SetVisible(bool value)
    {
        if (handle == nullptr)
            CreateHandle();

        if (visible != value)
        {
            visible = value;

            int showCommand = SW_HIDE;
            if (visible)
                showCommand = SW_SHOW;

            ::ShowWindow(static_cast<HWND>(handle), showCommand);
        }
    }

    bool GameWindow::GetFullscreenStyle() const
    {
        return ::GetWindowLong(static_cast<HWND>(handle), GWL_STYLE) == WS_POPUP;
    }

    void GameWindow::SetFullscreenStyle(bool value)
    {
        DWORD style = 0x00000000;
        if (value)
            style = WS_POPUP | WS_VISIBLE;
        else
            style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

        ::SetWindowLong(static_cast<HWND>(handle), GWL_STYLE, style);
        ::SetWindowPos(static_cast<HWND>(handle), HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREDRAW | SWP_NOACTIVATE | SWP_FRAMECHANGED | SWP_NOSENDCHANGING);
    }

    bool GameWindow::IsForeground() const
    {
        return ::GetForegroundWindow() == static_cast<HWND>(handle);
    }

    void* GameWindow::GetHandle() const
    {
        return handle;
    }

    void* GameWindow::GetDisplayHandle() const
    {
        return nullptr;
    }

    void GameWindow::OnCreated()
    {
    }

    void GameWindow::OnDestroy()
    {
    }

    void GameWindow::OnSnapShot()
    {
    }

    bool GameWindow::OnCommand(int /*commandID*/, int /*controlID*/, void* /*handle*/)
    {
        return false;
    }

    bool GameWindow::OnPaint()
    {
        return false;
    }

    void GameWindow::CreateHandle()
    {
        WNDCLASSEX windowClass;
        windowClass.cbSize = sizeof(windowClass);
        windowClass.style = 0;
        windowClass.lpfnWndProc = &Internal::WindowProcedure;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = sizeof(this);
        windowClass.hInstance = GetModuleHandle(nullptr);
        windowClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
        windowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
        windowClass.lpszMenuName = nullptr;
        windowClass.lpszClassName = ClassName;
        windowClass.hIconSm = windowClass.hIcon;
        RegisterClassEx(&windowClass);

        handle = static_cast<void*>(::CreateWindowEx(0x00000000, ClassName, "", WS_OVERLAPPEDWINDOW,
                                                     CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                                     nullptr, nullptr, GetModuleHandle(nullptr), this));
    }

    static const char* INSTANCE_NAME = "inst";

    static GameWindow* GetGameWindow(HWND windowHandle)
    {
        return reinterpret_cast<GameWindow*>(::GetProp(windowHandle, INSTANCE_NAME));
    }

    static void SetGameWindow(HWND windowHandle, GameWindow* value)
    {
        if (value)
            ::SetProp(windowHandle, INSTANCE_NAME, reinterpret_cast<HANDLE>(value));
        else
            ::RemoveProp(windowHandle, INSTANCE_NAME);
    }

    LRESULT CALLBACK GameWindow::Internal::WindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
            case WM_PAINT:
                if (GetGameWindow(windowHandle)->OnPaint())
                    return 0;

                break;
            case WM_KEYDOWN:
                {
                    const bool previousKeyState = (lParam & (1 << 30)) != 0;
                    if (previousKeyState == false)
                        GetGameWindow(windowHandle)->RaiseKeyDownEvent(static_cast<Key::Code>(wParam));
                }
                return 0;
            case WM_KEYUP:
                GetGameWindow(windowHandle)->RaiseKeyUpEvent(static_cast<Key::Code>(wParam));
                return 0;
            case WM_MOUSEMOVE:
                GetGameWindow(windowHandle)->RaiseMouseMoveEvent(LOWORD(lParam), HIWORD(lParam));
                return 0;
            case WM_LBUTTONDOWN:
                GetGameWindow(windowHandle)->RaiseMouseLeftButtonDownEvent(LOWORD(lParam), HIWORD(lParam));
                return 0;
            case WM_LBUTTONUP:
                GetGameWindow(windowHandle)->RaiseMouseLeftButtonUpEvent(LOWORD(lParam), HIWORD(lParam));
                return 0;
            case WM_MBUTTONDOWN:
                GetGameWindow(windowHandle)->RaiseMouseMiddleButtonDownEvent(LOWORD(lParam), HIWORD(lParam));
                return 0;
            case WM_MBUTTONUP:
                GetGameWindow(windowHandle)->RaiseMouseMiddleButtonUpEvent(LOWORD(lParam), HIWORD(lParam));
                return 0;
            case WM_RBUTTONDOWN:
                GetGameWindow(windowHandle)->RaiseMouseRightButtonDownEvent(LOWORD(lParam), HIWORD(lParam));
                return 0;
            case WM_RBUTTONUP:
                GetGameWindow(windowHandle)->RaiseMouseRightButtonUpEvent(LOWORD(lParam), HIWORD(lParam));
                return 0;
            case WM_MOUSEWHEEL:
                GetGameWindow(windowHandle)->RaiseMouseWheelEvent(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
                return 0;
            case WM_HOTKEY:
                if (wParam == IDHOT_SNAPDESKTOP ||
                    wParam == IDHOT_SNAPWINDOW)
                {
                    GetGameWindow(windowHandle)->OnSnapShot();
                    return 0;
                }
                break;
            case WM_COMMAND:
                {
                    const int commandID = HIWORD(wParam);
                    const int controlID = LOWORD(wParam);
                    void* handle = reinterpret_cast<void*>(lParam);
                    if (GetGameWindow(windowHandle)->OnCommand(commandID, controlID, handle))
                        return 0;
                }
                break;
            case WM_ENTERSIZEMOVE:
                GetGameWindow(windowHandle)->isUserSizing = true;
                return 0;
            case WM_EXITSIZEMOVE:
                {
                    RECT clientRect = { 0, 0, 0, 0 };
                    ::GetClientRect(windowHandle, &clientRect);
                    const Point2 newSize = Point2(clientRect.right - clientRect.left,
                                                  clientRect.bottom - clientRect.top);
                    GameWindow* o = GetGameWindow(windowHandle);
                    o->isUserSizing = false;
                    if (o->size != newSize)
                    {
                        o->size = newSize;
                        o->RaiseResizedEvent();
                    }
                }
                return 0;
            case WM_MOVE:
                {
                    RECT windowRect;
                    ::GetWindowRect(windowHandle, &windowRect);

                    GameWindow* o = GetGameWindow(windowHandle);
                    o->position = Point2(windowRect.left, windowRect.top);
                }
                return 0;
            case WM_SIZE:
                {
                    GameWindow* o = GetGameWindow(windowHandle);
                    if (wParam != SIZE_MINIMIZED)
                    {
                        if (wParam != SIZE_RESTORED ||
                            o->isUserSizing == false)
                        {
                            o->size = Point2(LOWORD(lParam), HIWORD(lParam));
                            o->RaiseResizedEvent();
                        }
                    }
                }
                return 0;
            case WM_CREATE:
                {
                     const CREATESTRUCT* createStruct = reinterpret_cast<const CREATESTRUCT*>(lParam);

                    GameWindow* o = reinterpret_cast<GameWindow*>(createStruct->lpCreateParams);
                    SetGameWindow(windowHandle, o);
                    o->OnCreated();

                    // RegisterHotKey(windowHandle, IDHOT_SNAPDESKTOP, 0,       VK_SNAPSHOT);
                    // RegisterHotKey(windowHandle, IDHOT_SNAPWINDOW,  MOD_ALT, VK_SNAPSHOT);
                }
                return 0;
            case WM_DESTROY:
                // UnregisterHotKey(windowHandle, IDHOT_SNAPWINDOW);
                // UnregisterHotKey(windowHandle, IDHOT_SNAPDESKTOP);

                GameWindow* o = GetGameWindow(windowHandle);
                o->OnDestroy();
                RemoveProp(windowHandle, nullptr);
                PostQuitMessage(0);
                return 0;
        }

        return DefWindowProc(windowHandle, message, wParam, lParam);
    }
}