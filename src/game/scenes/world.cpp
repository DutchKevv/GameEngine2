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
	// ShapeCube cube;

	void init()
	{
		std::cout << "init world \n";

		addChild(new ShapeCube);
	}
	void draw()
	{
		std::cout << "World draw \n";
		glEnable(GL_DEPTH_TEST);
		Scene::draw();
		glDisable(GL_DEPTH_TEST);
	}
};