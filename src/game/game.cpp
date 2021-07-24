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

		WorldScene worldScene;

		engine.addScene(&worldScene);

		engine.start();
	}
};