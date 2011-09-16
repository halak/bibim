#include <Bibim/TestBed.h>
#include <Bibim/GameFramework.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GameModuleTree.h>
#include <Bibim/GameWindow.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/PipedAssetProvider.h>
#include <Bibim/SourceTexture2D.h>
using namespace Bibim;

class SpriteTest : public GameFramework
{
    SourceTexture2DPtr texture;

    protected:
        virtual void Initialize()
        {
            GameFramework::Initialize();
            GetWindow()->SetTitle("Sprite");

            GameAssetStorage*   gas = new GameAssetStorage(GetModules());
            PipedAssetProvider* pap = new PipedAssetProvider(gas, "TestAssets");

            GameModuleNode* gasNode = GetModules()->GetRoot()->AttachChild(gas);
            gasNode->AttachChild(pap);

            texture = static_cast<SourceTexture2D*>(gas->Load("Hello.png"));
        }

        virtual void Finalize()
        {
            texture.Reset();

            GameFramework::Finalize();
        }

        virtual void Draw()
        {
            GetGraphicsDevice()->Clear();
        }
};

void Bibim::TestBed::Sprite(CommandLines commands)
{
    SpriteTest app;
    app.Run();
}