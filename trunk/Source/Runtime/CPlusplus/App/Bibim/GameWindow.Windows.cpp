#include <Bibim/PCH.h>
#include <Bibim/GameWindow.Windows.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>

    namespace Bibim
    {
        struct GameWindow::Fields
        {
            static const char* ClassName;

            HWND Handle;

            Fields()
                : Handle(nullptr)
            {
            }
            
            void CreateHandle(GameWindow* owner);

            static LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
        };

        const char* GameWindow::Fields::ClassName = "Halak.Bibim.GameWindow";

        GameWindow::GameWindow()
            : mPointer(new Fields()),
              m(*mPointer),
              visible(false)
        {
        }

        GameWindow::~GameWindow()
        {
            Close();
            delete mPointer;
        }

        void GameWindow::MoveToScreenCenter()
        {
            if (m.Handle == nullptr)
                m.CreateHandle(this);

            RECT windowRect = { 0, 0, 0, 0 };
            if (GetWindowRect(m.Handle, &windowRect))
            {
                const SIZE screenSize = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
                const SIZE windowSize = { windowRect.right - windowRect.left, windowRect.bottom - windowRect.top };
                const POINT windowPosition = { (screenSize.cx - windowSize.cx) / 2, (screenSize.cy - windowSize.cy) / 2 };

                SetPosition(Point(windowPosition.x, windowPosition.y));
            }
        }

        void GameWindow::Close()
        {
            if (m.Handle == nullptr)
                return;

            DestroyWindow(m.Handle);
        }

        const String& GameWindow::GetTitle() const
        {
            return title;
        }

        void GameWindow::SetTitle(const String& value)
        {
            if (m.Handle == nullptr)
                m.CreateHandle(this);

            if (title != value)
            {
                title = value;
                
                ::SetWindowText(m.Handle, title.CStr());
            }
        }

        Point GameWindow::GetPosition() const
        {
            return position;
        }

        void GameWindow::SetPosition(Point value)
        {
            if (m.Handle == nullptr)
                m.CreateHandle(this);

            if (GetPosition() != value)
            {
                position = value;
                
                ::SetWindowPos(m.Handle, NULL, position.X, position.Y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
            }
        }

        Point GameWindow::GetSize() const
        {
            return size;
        }

        void GameWindow::SetSize(Point value)
        {
            if (m.Handle == nullptr)
                m.CreateHandle(this);

            if (GetSize() != value)
            {
                size = value;

                const DWORD exWindowStyle = static_cast<DWORD>(GetWindowLong(m.Handle, GWL_EXSTYLE));
                const DWORD windowStyle = static_cast<DWORD>(GetWindowLong(m.Handle, GWL_STYLE));
                const BOOL hasMenu = GetMenu(m.Handle) != NULL ? TRUE : FALSE;
                RECT windowRect = { 0, 0, size.X, size.Y };
                ::AdjustWindowRectEx(&windowRect, windowStyle, hasMenu, exWindowStyle);

                const SIZE windowSize = { windowRect.right - windowRect.left, windowRect.bottom - windowRect.top };
                ::SetWindowPos(m.Handle, NULL, 0, 0, windowSize.cx, windowSize.cy, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
            }
        }

        bool GameWindow::GetVisible() const
        {
            return visible;
        }

        void GameWindow::SetVisible(bool value)
        {
            if (m.Handle == nullptr)
                m.CreateHandle(this);

            if (visible != value)
            {
                visible = value;

                int showCommand = SW_HIDE;
                if (visible)
                    showCommand = SW_SHOW;

                ::ShowWindow(m.Handle, showCommand);
            }
        }

        bool GameWindow::GetActive() const
        {
            return ::GetForegroundWindow() == m.Handle;
        }

        void* GameWindow::GetHandle() const
        {
            return m.Handle;
        }

        void GameWindow::OnCreated()
        {
        }

        void GameWindow::OnDestroy()
        {
        }

        void GameWindow::OnMouseWheel(int delta)
        {
            MouseWheel().Emit(delta);
        }

        void GameWindow::Fields::CreateHandle(GameWindow* owner)
        {
            WNDCLASSEX windowClass;
            windowClass.cbSize = sizeof(windowClass);
            windowClass.style = CS_DBLCLKS;
            windowClass.lpfnWndProc = &WindowProcedure;
            windowClass.cbClsExtra = 0;
            windowClass.cbWndExtra = sizeof(owner);
            windowClass.hInstance = GetModuleHandle(NULL);
            windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
            windowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
            windowClass.lpszMenuName = NULL;
            windowClass.lpszClassName = ClassName;
            windowClass.hIconSm = windowClass.hIcon;
            RegisterClassEx(&windowClass);

            Handle = ::CreateWindowEx(0x00000000, ClassName, ClassName, WS_OVERLAPPEDWINDOW,
                                      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                      NULL, NULL, GetModuleHandle(NULL), owner);
        }

        LRESULT CALLBACK GameWindow::Fields::WindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
        {
            static const char* instanceName = "inst";

            GameWindow* gameWindow = reinterpret_cast<GameWindow*>(GetProp(windowHandle, instanceName));

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
                    gameWindow->OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA);
                    break;
                case WM_DESTROY:
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