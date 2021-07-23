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
		glEnable(GL_DEPTH_TEST);
		cube.draw();
		glDisable(GL_DEPTH_TEST);
	}
};