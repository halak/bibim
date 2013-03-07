#include <Bibim/PCH.h>
#include <Bibim/GameFramework.Android.h>

namespace Bibim
{
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
        GameFrameworkBase::Construct(resolutionWidth,
                                     resolutionHeight,
                                     String::Empty);
    }
}