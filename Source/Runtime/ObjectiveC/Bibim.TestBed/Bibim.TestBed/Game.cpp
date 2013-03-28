#include "Game.h"
#include <Bibim/GraphicsDevice.h>
#include <Bibim/Color.h>
#include <Bibim/Startup.h>
#include <Bibim/Log.h>
using namespace Bibim;

void Game::Initialize()
{
    StandardGame::Initialize("HELLO", "1.0.0", nullptr);
    SetClearColor(Color(0, 0, 255));
    Log::Warning("HELLO");
}

void Game::Finalize()
{
    StandardGame::Finalize();
}

void Game::Update(float dt, int timestamp)
{
    StandardGame::Update(dt, timestamp);
}

void Game::Draw()
{
    StandardGame::Draw();
}

BBMain(Game);