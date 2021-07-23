#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include "../../engine/scene.cpp"
#include "../../shape/triangle.cpp"
#include "../../shape/cube.cpp"

class WorldScene : public Scene
{
public:
	ShapeCube cube;

	void init()
	{
		cube.init();
	}
	void draw()
	{
		std::cout << "33333";
		cube.draw();
	}
};