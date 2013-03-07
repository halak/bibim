#include <Bibim/PCH.h>
#include <Bibim/GameFrameworkBase.h>
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

    GameFrameworkBase::GameFrameworkBase()
    {
    }

    GameFrameworkBase::~GameFrameworkBase()
    {
        delete modules;
    }

    void GameFrameworkBase::Construct(int resolutionWidth, int resolutionHeight, const String& startupArgs)
    {
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
        timestamp = 0;
        window->SetSize(graphicsDevice->GetResolution());

        modules->GetRoot()->AttachChild(window);
        modules->GetRoot()->AttachChild(graphicsDevice);
        modules->GetRoot()->AttachChild(mainTimeline);

        this->startupArgs = startupArgs;
    }

    void GameFrameworkBase::Exit()
    {
        window->Close();
    }

    void GameFrameworkBase::SetFixedTimeStep(bool value)
    {
        fixedTimeStep = value;
    }

    void GameFrameworkBase::SetFixedElapsedTime(float value)
    {
        fixedElapsedTime = Math::Max(value, 0.0001f);
        desiredFPS = Math::Min(static_cast<int>(1.0f / fixedElapsedTime), GeneralFPS);
    }

    void GameFrameworkBase::SetMaxTimeInOneFrame(float value)
    {
        maxTimeInOneFrame = Math::Max(value, 0.0001f);
    }

    float GameFrameworkBase::GetFPS() const
    {
        if (timestamps.size() >= 2)
            return static_cast<float>(timestamps.size() - 1) / (timestamps.back() - timestamps.front());
        else
            return 0.0f;
    }

    void GameFrameworkBase::Initialize()
    {
        graphicsDevice->SetWindow(window);
        window->SetVisible(true);
    }

    void GameFrameworkBase::Finalize()
    {
        window->SetVisible(false);
    }

    void GameFrameworkBase::PostInitialize()
    {
        timestamps.push_back(Clock::GetCurrent());
    }

    void GameFrameworkBase::StepFrame()
    {
        float previousTime = timestamps.back();

        const float currentTime = Clock::GetCurrent();
        const float elapsedTime = currentTime - previousTime;

        if (fixedTimeStep)
        {
            const float dt = fixedElapsedTime;
            float time = Math::Min(elapsedTime, maxTimeInOneFrame);
            if (time < dt)
                return;

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

    }

    void GameFrameworkBase::Update(float dt, int timestamp)
    {
        mainTimeline->Update(dt, timestamp);
    }

    void GameFrameworkBase::Draw()
    {
    }

    void GameFrameworkBase::BeginDraw()
    {
        graphicsDevice->BeginDraw();
    }

    void GameFrameworkBase::EndDraw()
    {
        graphicsDevice->EndDraw();
        graphicsDevice->Present();
    }
}