#include "Game.h"
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Color.h>
#include <Bibim/Startup.h>
using namespace Bibim;

void Game::Initialize()
{
    GameFramework::Initialize();
}

void Game::Finalize()
{
    GameFramework::Finalize();
}

void Game::Update(float dt, int timestamp)
{
    GameFramework::Update(dt, timestamp);
}

void Game::Draw()
{
    GetGraphicsDevice()->Clear(Color(255, 0, 0));
    GameFramework::Draw();
}

BBMain(Game);