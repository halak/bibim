#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_IOS))

#include <Bibim/GameFramework.iOS.h>
#include <Bibim/Environment.h>
#include <Bibim/FileStream.h>
#include <Bibim/GameFramework.h>
#include <Bibim/GameModuleTree.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GameWindow.h>
#include <Bibim/IME.h>
#include <Bibim/Log.h>
#include <Bibim/Key.h>
#include <Bibim/Point2.h>
using namespace Bibim;

namespace Bibim
{
    GameFramework* GameFramework::SingletonInstance = nullptr;

    GameFramework::GameFramework()
        : ime(nullptr)
    {
        Construct(0, 0);
    }

    GameFramework::GameFramework(int width, int height)
        : ime(nullptr)
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

        GameModuleNode* moduleRoot = GetModules()->GetRoot();
        ime = static_cast<IME*>(moduleRoot->FindChildByClassID(IME::ClassID));
    }

    void GameFramework::update()
    {
        UpdateFrame();
    }

    void GameFramework::draw()
    {
        DrawFrame();
    }
}

#endif