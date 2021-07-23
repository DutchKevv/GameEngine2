#include <iostream>
#include <string>

#include "../engine/engine.cpp"
#include "./scenes/world.cpp"

using std::string;

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

		// ShapeTriangle triangle;
		// ShapeCube cube;
		// // triangle.init();
		// cube.init();
	}
};