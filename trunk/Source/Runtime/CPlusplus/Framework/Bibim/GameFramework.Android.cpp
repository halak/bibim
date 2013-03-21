#include <Bibim/PCH.h>
#include <Bibim/GameFramework.Android.h>
#include <Bibim/Point2.h>

namespace Bibim
{
    GameFramework::GameFramework()
    {
        Construct(0, 0);
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
        GameFrameworkBase::Construct(width, height, String::Empty);
    }
    
    void GameFramework::init()
    {
        Initialize();
        PostInitialize();
    }

    void GameFramework::step()
    {
        StepFrame();
    }
}