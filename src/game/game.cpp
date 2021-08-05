#include <iostream>
#include "game.h"
#include "../engine/engine.h"
#include "./scenes/world.h"

void Game::init()
{
	Engine engine;
	engine.init();

	engine.addScene(new WorldScene());

	engine.start();
}