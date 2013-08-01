#include <Bibim/Config.h>
#include <Bibim/GameFramework.Windows.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

namespace Bibim
{
    GameFramework::GameFramework()
    {
        Construct(800, 600);
    }

    GameFramework::GameFramework(int width, int height)
    {
        Construct(width, height);
    }

    GameFramework::~GameFramework()
    {
    }

    void GameFramework::Construct(int width, int height)
    {
        _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

        LPWSTR commandLine = ::GetCommandLineW();
        char utf8CommandLine[1024];
        const int length = ::WideCharToMultiByte(CP_UTF8,
                                                 0,
                                                 commandLine, wcslen(commandLine),
                                                 utf8CommandLine, sizeof(utf8CommandLine),
                                                 NULL, NULL);
        utf8CommandLine[length] = '\0';
        GameFrameworkBase::Construct(width, height, utf8CommandLine);
    }

    void GameFramework::Run()
    {
        Initialize();
        PostInitialize();

        MSG msg = { 0, };
        for (;;)
        {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT)
                {
                    Finalize();
                    break;
                }
            }
            else
            {
                StepFrame();                
                Sleep(1);
            }
        }
    }
}