#include <Bibim/PCH.h>
#include <Bibim/GameWindow.Windows.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#   include <vector>

    namespace Bibim
    {
        static const char* ClassName = "Halak.Bibim.GameWindow";

        struct GameWindow::Internal
        {
            static LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
        };

        GameWindow::GameWindow()
            : handle(nullptr),
              visible(false)
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

        bool GameWindow::GetActive() const
        {
            return ::GetForegroundWindow() == static_cast<HWND>(handle);
        }

        void* GameWindow::GetHandle() const
        {
            return handle;
        }

        void GameWindow::OnCreated()
        {
        }

        void GameWindow::OnDestroy()
        {
        }

        void GameWindow::OnMouseWheel(int delta)
        {
            SetWheel(GetWheel() + delta);
        }

        void GameWindow::CreateHandle()
        {
            WNDCLASSEX windowClass;
            windowClass.cbSize = sizeof(windowClass);
            windowClass.style = CS_DBLCLKS;
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

            handle = static_cast<void*>(::CreateWindowEx(0x00000000, ClassName, ClassName, WS_OVERLAPPEDWINDOW,
                                                         CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                                         nullptr, nullptr, GetModuleHandle(nullptr), this));
        }

        LRESULT CALLBACK GameWindow::Internal::WindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
        {
            static const char* instanceName = "inst";
            GameWindow* gameWindow = nullptr;

            switch (message)
            {
                case WM_CREATE:
                    {
                         const CREATESTRUCT* createStruct = reinterpret_cast<const CREATESTRUCT*>(lParam);

                        SetProp(windowHandle, instanceName, reinterpret_cast<HANDLE>(createStruct->lpCreateParams));
                        gameWindow = reinterpret_cast<GameWindow*>(createStruct->lpCreateParams);
                        gameWindow->OnCreated();
                    }
                    break;
                case WM_MOUSEWHEEL:
                    gameWindow = reinterpret_cast<GameWindow*>(GetProp(windowHandle, instanceName));
                    gameWindow->OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
                    break;
                case WM_DESTROY:
                    gameWindow = reinterpret_cast<GameWindow*>(GetProp(windowHandle, instanceName));
                    gameWindow->OnDestroy();
                    RemoveProp(windowHandle, instanceName);
                    PostQuitMessage(0);
                    break;
                default:
                    return DefWindowProc(windowHandle, message, wParam, lParam);
            }

            return 0;
        }
    }

#endif