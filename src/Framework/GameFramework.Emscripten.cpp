#include <Bibim/Config.h>
#if (defined(BIBIM_PLATFORM_EMSCRIPTEN))

#include <Bibim/GameFramework.Emscripten.h>
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
#include <emscripten.h>
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

    void GameFramework::DoStep()
    {
        if (GameFramework::SingletonInstance == nullptr)
        {
            int width;
            int height;
            int fullscreen;
            emscripten_get_canvas_size(&width, &height, &fullscreen);

            if (width <= 0 && height <= 0)
                return;

            GameFramework::SingletonInstance = GameFramework::Create();
            GameFramework::SingletonInstance->GetWindow()->SetSize(Point2(width, height));
            GameFramework::SingletonInstance->init();
        }

        GameFramework::SingletonInstance->StepFrame();
    }
}

int main(int argc, const char** argv)
{
    // Environment::Setup(ToString(env, localeName), ToString(env, workingDirectory));
    // FileStream::SetAndroidAssetManager(AAssetManager_fromJava(env, assetManager));

    emscripten_set_main_loop(&GameFramework::DoStep, 60, false);
}

#endif