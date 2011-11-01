#include <Bibim/TestBed.h>
#include <Bibim/GameFramework.h>
#include <Bibim/Clock.h>
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

class UISample : public GameFramework
{
    GameAssetStorage* storage;
    UIDomain* uiDomain;
    UIRenderer* uiRenderer;
    UIRenderBufferPtr buffer;
    SourceTexture2DPtr texture1;

    protected:
        virtual void Initialize()
        {
            GameFramework::Initialize();
            GetWindow()->SetTitle("UI");

            GameAssetStorage*   gas = new GameAssetStorage(GetModules());
            PipedAssetProvider* pap = new PipedAssetProvider(gas, "BibimAssetPipe", "UISample");
            FileAssetProvider*  fap = new FileAssetProvider(gas);

            UIWindowPtr window = new UIWindow();
            window->SetFrame(new UIFixedFrame(RectF(0, 0, 800, 600)));

            UIDomain*           uid = new UISimpleDomain(window);
            UIRenderer*         uir = new UIRenderer(GetGraphicsDevice());

            GameModuleNode* gasNode = GetModules()->GetRoot()->AttachChild(gas);
            gasNode->AttachChild(fap);
            gasNode->AttachChild(pap);

            GameModuleNode* uiNode = GetModules()->GetRoot()->AttachChild(uid);
            uiNode->AttachChild(uir);

            storage = gas;
            uiDomain = uid;
            uiRenderer = uir;

            texture1 = static_cast<SourceTexture2D*>(gas->Load("Asset\\BigHello"));

            buffer = new UIRenderBuffer(1024 * 64);
            ImagePtr image = new Image(texture1);
            UIDrawingContext context(uiRenderer, buffer);
            for (float x = 0.0f; x < 800.0f; x+=5.0f)
            {
                for (float y = 0.0f; y < 600.0f; y+= 5.0f)
                    context.Draw(RectF(x, y, 10.0f, 10.0f), RectF(x, y, 10.0f, 10.0f), image, false, false);
            }
            buffer->Flush();
        }


        virtual void Finalize()
        {
            GameFramework::Finalize();
        }

        virtual void Draw()
        {
            GetGraphicsDevice()->Clear();
            UIDrawingContext context(uiRenderer, buffer);
            //uiRenderer->Begin();
            //ImagePtr image = new Image(texture1);
            //int i = 0;
            //for (float x = 0.0f; x < 800.0f; x+=5.0f)
            //{
            //    for (float y = 0.0f; y < 600.0f; y+= 5.0f,i++)
            //        context.Draw(RectF(x, y, 10.0f, 10.0f), RectF(x, y, 10.0f, 10.0f), image, false, false);
            //}
            //uiRenderer->End();
            //UIDrawingContext context(uiRenderer, buffer);
            //uiRenderer->Begin();
            //context.Draw(RectF(100.0f, 100.0f, 100.0f, 100.0f), RectF(100.0f, 100.0f, 100.0f, 100.0f), image, false, false);
            //uiRenderer->End();
            for (int i = 0; i < 100; i++)
                uiRenderer->Draw(buffer);
        }
};

void Bibim::TestBed::UI(CommandLines commands)
{
    UISample app;
    app.Run();
}