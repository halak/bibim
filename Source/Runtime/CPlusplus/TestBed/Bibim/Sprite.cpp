#include <Bibim/TestBed.h>
#include <Bibim/GameFramework.h>
#include <Bibim/GameAssetStorage.h>
#include <Bibim/GameModuleNode.h>
#include <Bibim/GameModuleTree.h>
#include <Bibim/GameWindow.h>
#include <Bibim/GraphicsDevice.h>
#include <Bibim/PipedAssetProvider.h>
#include <Bibim/FileAssetProvider.h>
#include <Bibim/SourceTexture2D.h>
#include <Bibim/UI.h>
using namespace Bibim;

class SpriteTest : public GameFramework
{
    GameAssetStorage* storage;
    UIDomain* uiDomain;
    UIRenderer* uiRenderer;
    SourceTexture2DPtr texture1;
    SourceTexture2DPtr texture2;

    protected:
        virtual void Initialize()
        {
            GameFramework::Initialize();
            GetWindow()->SetTitle("Sprite");

            GameAssetStorage*   gas = new GameAssetStorage(GetModules());
            PipedAssetProvider* pap = new PipedAssetProvider(gas, "TestAssets", "SpriteSample");
//          FileAssetProvider*  fap = new FileAssetProvider(gas);

            UIWindowPtr window = new UIWindow();
            window->SetFrame(new UIFixedFrame(RectF(0, 0, 800, 600)));

            UIDomain*           uid = new UISimpleDomain(window);
            UIRenderer*         uir = new UIRenderer(GetGraphicsDevice());

            GameModuleNode* gasNode = GetModules()->GetRoot()->AttachChild(gas);
//          gasNode->AttachChild(fap);
            gasNode->AttachChild(pap);

            GameModuleNode* uiNode = GetModules()->GetRoot()->AttachChild(uid);
            uiNode->AttachChild(uir);

            gas->Preload("Asset\\BigHello");
            gas->Preload("Asset\\Background");

            //texture1 = static_cast<SourceTexture2D*>(gas->Load("Asset\\BigHello"));
            //texture2 = static_cast<SourceTexture2D*>(gas->Load("Asset\\Background"));

            storage = gas;
            uiDomain = uid;
            uiRenderer = uir;
        }

        virtual void Finalize()
        {
            texture1.Reset();
            texture2.Reset();

            GameFramework::Finalize();
        }

        virtual void Draw()
        {
            GameAssetStorage::LoadingStatus status = storage->GetBackgroundLoadingStatus();
            char title[128];
            sprintf(title, "%d/%d", status.LoadedBytes, status.TotalBytes);
            GetWindow()->SetTitle(title);

            GetGraphicsDevice()->Clear();
            struct Handler : UIHandledDrawingContext::IHandler
            {
                SpriteTest* app;
                Handler(SpriteTest* app)
                    : app(app)
                {
                }

                virtual void OnBegan(UIHandledDrawingContext& context)
                {
                    //context.Draw(Vector2(0.0f, 0.0f),   app->texture1);
                    //context.Draw(Vector2(256.0f, 0.0f), app->texture2);
                }
            };
            Handler handler(this);
            UIHandledDrawingContext context(uiRenderer, &handler);
            context.Draw(uiDomain->GetRoot());
        }
};

void Bibim::TestBed::Sprite(CommandLines commands)
{
    SpriteTest app;
    app.Run();
}