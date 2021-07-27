#pragma once

#include <iostream>
#include "../engine/engine.cpp"
#include "./scenes/world.cpp"

class Game
{
public:
	void init()
	{
		Engine engine;
		engine.init();

		engine.addScene(new WorldScene());

		engine.start();
	}
};