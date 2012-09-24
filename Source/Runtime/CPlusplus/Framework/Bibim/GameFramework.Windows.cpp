#include <Bibim/PCH.h>
#include <Bibim/GameFramework.Windows.h>
#include <Bibim/Assert.h>
#include <Bibim/Clock.h>
#include <Bibim/GameModuleTree.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Math.h>
#include <Bibim/Startup.h>
#include <Bibim/Timeline.h>
#include <Bibim/GameWindow.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))

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
            delete modules;
        }

        void GameFramework::Construct(int resolutionWidth, int resolutionHeight)
        {
            _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
            Startup::All();

            modules = new GameModuleTree();
            window = new GameWindow();
            if (resolutionWidth == 0 || resolutionHeight == 0)
                graphicsDevice = new GraphicsDevice();
            else
                graphicsDevice = new GraphicsDevice(resolutionWidth, resolutionHeight);
            mainTimeline = new Timeline();
            fixedTimeStep = true;
            fixedElapsedTime = 1.0f / static_cast<float>(GeneralFPS);
            maxTimeInOneFrame = 1.0f;
            desiredFPS = GeneralFPS;
            window->SetSize(graphicsDevice->GetResolution());

            modules->GetRoot()->AttachChild(window);
            modules->GetRoot()->AttachChild(graphicsDevice);
            modules->GetRoot()->AttachChild(mainTimeline);

            LPWSTR commandLine = ::GetCommandLineW();
            char utf8CommandLine[1024];
            const int length = ::WideCharToMultiByte(CP_UTF8,
                                                     0,
                                                     commandLine, wcslen(commandLine),
                                                     utf8CommandLine, sizeof(utf8CommandLine),
                                                     NULL, NULL);
            utf8CommandLine[length] = '\0';
            startupArgs = utf8CommandLine;

            //SYSTEM_INFO systemInfo = { 0, };
            //GetSystemInfo(&systemInfo);
            //BBAssert(systemInfo.dwNumberOfProcessors > 0);
            //if (systemInfo.dwNumberOfProcessors == 1)
            //    sleepDuration = 1;
            //else
            //    sleepDuration = 0;
        }

        void GameFramework::Run()
        {
            Initialize();

            int  timestamp = 0;
            float previousTime = Clock::GetCurrent();
            timestamps.push_back(previousTime);

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
                    const float currentTime = Clock::GetCurrent();
                    const float elapsedTime = currentTime - previousTime;

                    if (fixedTimeStep)
                    {
                        const float dt = fixedElapsedTime;
                        float time = Math::Min(elapsedTime, maxTimeInOneFrame);
                        if (time < dt)
                        {
                            Sleep(1);
                            continue;
                        }

                        for (/**/; time >= dt; time -= dt, previousTime += dt)
                            Update(dt, timestamp++);
                    }
                    else
                    {
                        Update(currentTime - previousTime, timestamp++);
                        previousTime = currentTime;
                    }

                    BeginDraw();
                    Draw();
                    EndDraw();

                    timestamps.push_back(currentTime);
                    if (static_cast<int>(timestamps.size()) > desiredFPS)
                        timestamps.pop_front();

                    Sleep(1);
                }
            }
        }

        void GameFramework::Exit()
        {
            window->Close();
        }

        void GameFramework::SetFixedTimeStep(bool value)
        {
            fixedTimeStep = value;
        }

        void GameFramework::SetFixedElapsedTime(float value)
        {
            fixedElapsedTime = Math::Max(value, 0.0001f);
            desiredFPS = Math::Min(static_cast<int>(1.0f / fixedElapsedTime), GeneralFPS);
        }

        void GameFramework::SetMaxTimeInOneFrame(float value)
        {
            maxTimeInOneFrame = Math::Max(value, 0.0001f);
        }

        float GameFramework::GetFPS() const
        {
            if (timestamps.size() >= 2)
                return static_cast<float>(timestamps.size() - 1) / (timestamps.back() - timestamps.front());
            else
                return 0.0f;
        }

        void GameFramework::Initialize()
        {
            graphicsDevice->SetWindow(window);
            window->SetVisible(true);
        }

        void GameFramework::Finalize()
        {
            window->SetVisible(false);
        }

        void GameFramework::Update(float dt, int timestamp)
        {
            mainTimeline->Update(dt, timestamp);
        }

        void GameFramework::Draw()
        {
        }

        void GameFramework::BeginDraw()
        {
            graphicsDevice->BeginDraw();
        }

        void GameFramework::EndDraw()
        {
            graphicsDevice->EndDraw();
            graphicsDevice->Present();
        }

        //void GameFramework::ForceUpdateAllComponents(float dt, int timestamp)
        //{
        //    ForceUpdateComponent(structure->GetRoot(), dt, timestamp);
        //}

        //void GameFramework::ForceUpdateComponent(GameNode* node, float dt, int timestamp)
        //{
        //    if (node->GetComponent())
        //    {
        //        if (IUpdateable* updateableComponent = node->GetComponent()->QueryUpdateableInterface())
        //            updateableComponent->Update(dt, timestamp);
        //    }

        //    const GameNode::NodeCollection& children = node->GetChildren();
        //    for (GameNode::NodeCollection::const_iterator it = children.begin(); it != children.end(); it++)
        //        ForceUpdateComponent(*it, dt, timestamp);
        //}
    }

#endif