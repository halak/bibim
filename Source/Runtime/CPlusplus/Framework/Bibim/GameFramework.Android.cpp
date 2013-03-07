#include <Bibim/PCH.h>
#include <Bibim/GameFramework.Android.h>
#include <Bibim/Assert.h>
#include <Bibim/Clock.h>
#include <Bibim/GameModuleTree.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Math.h>
#include <Bibim/Startup.h>
#include <Bibim/Timeline.h>
#include <Bibim/GameWindow.h>

namespace Bibim
{
    static const int GeneralFPS = 60;

    GameFramework::GameFramework()
    {
        Construct(0, 0);
    }

    GameFramework::GameFramework(int resolutionWidth, int resolutionHeight)
    {
        Construct(resolutionWidth, resolutionHeight);
    }

    GameFramework::~GameFramework()
    {
    }

    void GameFramework::Construct(int resolutionWidth, int resolutionHeight)
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
        GameFrameworkBase::Construct(resolutionWidth, resolutionHeight, utf8CommandLine);
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