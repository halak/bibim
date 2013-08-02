#include <Bibim/TestBed.h>
#include <Bibim/GameFramework.h>
#include <Bibim/BitMask.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GameModuleTree.h>
#include <Bibim/GameWindow.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/PipedAssetProvider.h>
#include <Bibim/FileAssetProvider.h>
#include <Bibim/SourceTexture2D.h>
#include <Bibim/Script.h>
#include <Bibim/ScriptThread.h>
#include <Bibim/UI.h>
using namespace Bibim;

class BlendTest : public GameFramework
{
    GameAssetStorage* storage;
    UIDomain* uiDomain;
    UIRenderer* uiRenderer;

    protected:
        virtual void Initialize()
        {
            GameFramework::Initialize();
            GetWindow()->SetTitle("Blend - Bibim Samples");

            GameAssetStorage*   gas = new GameAssetStorage(GetModules());
            PipedAssetProvider* pap = new PipedAssetProvider(gas, PipedAssetProvider::DefaultPipeName, "BlendSample");
            FileAssetProvider*  fap = new FileAssetProvider(gas);

            UIWindowPtr window = new UIWindow();
            window->SetSize(800, 600);
            window->SetSizeMode(UIVisual::AbsoluteSize);

            UIDomain*   uid = new UISimpleDomain(window);
            UIRenderer* uir = new UIRenderer(GetGraphicsDevice(), gas, "Asset\\Shader");

            GameModuleNode* gasNode = GetModules()->GetRoot()->AttachChild(gas);
            gasNode->AttachChild(fap);
            gasNode->AttachChild(pap);

            GameModuleNode* uiNode = GetModules()->GetRoot()->AttachChild(uid);
            uiNode->AttachChild(uir);

            UILayoutPtr layout = static_cast<UILayout*>(gas->Load("Asset\\Blend"));
            uid->GetRoot()->AddChild(layout->GetRoot()->Clone());

            storage = gas;
            uiDomain = uid;
            uiRenderer = uir;
        }

        virtual void Finalize()
        {
            GameFramework::Finalize();
        }

        virtual void Draw()
        {
            UIDrawingContext context(uiRenderer);
            context.Draw(uiDomain->GetRoot());
        }
};

void Bibim::TestBed::Blend(CommandLines commands)
{
    BlendTest app;
    app.Run();
}