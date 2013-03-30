namespace Bibim
{
    GameModuleTree* GameFrameworkBase::GetModules() const
    {
        return modules;
    }

    GameWindow* GameFrameworkBase::GetWindow() const
    {
        return window;
    }

    GraphicsDevice* GameFrameworkBase::GetGraphicsDevice() const
    {
        return graphicsDevice;
    }

    Timeline* GameFrameworkBase::GetMainTimeline() const
    {
        return mainTimeline;
    }

    const String& GameFrameworkBase::GetStartupArgs() const
    {
        return startupArgs;
    }

    bool GameFrameworkBase::GetFixedTimeStep() const
    {
        return fixedTimeStep;
    }

    float GameFrameworkBase::GetFixedElapsedTime() const
    {
        return fixedElapsedTime;
    }

    float GameFrameworkBase::GetMaxTimeInOneFrame() const
    {
        return maxTimeInOneFrame;
    }
}