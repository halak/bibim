#include <Bibim/TestBed.h>
#include <Bibim/GameFramework.h>
#include <Bibim/Clock.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GameModuleTree.h>
#include <Bibim/GameWindow.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Image.h>
#include <Bibim/PipedAssetProvider.h>
#include <Bibim/FileAssetProvider.h>
#include <Bibim/SourceTexture2D.h>
#include <Bibim/Script.h>
#include <Bibim/ScriptThread.h>
#include <Bibim/UI.h>
using namespace Bibim;

class UISample : public GameFramework
{
    GameAssetStorage* storage;
    UIDomain* uiDomain;
    UIRenderer* uiRenderer;
    UIOpacityMaskEffectPtr maskEffect;

    protected:
        virtual void Initialize()
        {
            GameFramework::Initialize();
            GetWindow()->SetTitle("UI");

            GameAssetStorage*   gas = new GameAssetStorage(GetModules());
            PipedAssetProvider* pap = new PipedAssetProvider(gas, PipedAssetProvider::DefaultPipeName, "UISample");
            FileAssetProvider*  fap = new FileAssetProvider(gas);

            UIWindowPtr window = new UIWindow();
            window->SetFrame(new UIFixedFrame(RectF(0, 0, 800, 600)));

            UIDomain*           uid = new UISimpleDomain(window);
            UIRenderer*         uir = new UIRenderer(GetGraphicsDevice(), gas, "Asset\\Shader");

            GameModuleNode* gasNode = GetModules()->GetRoot()->AttachChild(gas);
            gasNode->AttachChild(fap);
            gasNode->AttachChild(pap);

            GameModuleNode* uiNode = GetModules()->GetRoot()->AttachChild(uid);
            uiNode->AttachChild(uir);

            UISprite* sprite = new UISprite();
            sprite->SetFrame(UIFittedFrame::Instance);
            sprite->SetImage(new Image(static_cast<Texture2D*>(gas->Load("Asset\\Background"))));
            sprite->SetEffectMap(new UIEffectMap());
            maskEffect = new UIOpacityMaskEffect(new Image(static_cast<Texture2D*>(gas->Load("Asset\\OpacityMap"))));
            sprite->GetEffectMap()->Insert(maskEffect);
            //sprite->GetEffectMap()->Insert(new UIColorMatrixEffect(Vector4(1.0f, 0.0f, 0.0f, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 0.0f)));
            uid->GetRoot()->AddChild(sprite);

            storage = gas;
            uiDomain = uid;
            uiRenderer = uir;

            //maskEffect->SetStartPoint(0.0f);
            //maskEffect->SetLength(0.05f);
            maskEffect->SetFill(UIOpacityMaskEffect::FanStyle);
        }


        virtual void Finalize()
        {
            maskEffect.Reset();
            GameFramework::Finalize();
        }

        virtual void Update(float dt, uint timestamp)
        {
            if (GetAsyncKeyState(VK_UP))
                maskEffect->SetStartPoint(maskEffect->GetStartPoint() + dt);
            if (GetAsyncKeyState(VK_DOWN))
                maskEffect->SetStartPoint(maskEffect->GetStartPoint() - dt);
        }

        virtual void Draw()
        {
            GetGraphicsDevice()->Clear();
            UIDrawingContext context(uiRenderer);
            context.Draw(uiDomain->GetRoot());
        }
};

void Bibim::TestBed::UI(CommandLines commands)
{
    UISample app;
    app.Run();
}