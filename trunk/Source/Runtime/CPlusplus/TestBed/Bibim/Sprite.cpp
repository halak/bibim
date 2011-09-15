#include <Bibim/TestBed.h>
#include <Bibim/GameFramework.h>
#include <Bibim/GameWindow.h>
#include <Bibim/GraphicsDevice.h>
using namespace Bibim;

class SpriteTest : public GameFramework
{
    protected:
        virtual void Initialize()
        {
            GetWindow()->SetTitle("Sprite");
            GameFramework::Initialize();
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