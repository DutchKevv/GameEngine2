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

		ShapeCube *cube1 = new ShapeCube();
		ShapeCube *cube2 = new ShapeCube();
		ShapeCube *cube3 = new ShapeCube();
		ShapeCube *cube4 = new ShapeCube();
		// ShapeCube cube2;
		// ShapeCube cube3;
		// ShapeCube cube4;

		addChild(cube1);
		addChild(cube2);
		addChild(cube3);
		addChild(cube4);
		// addChild(&cube2);
		// addChild(&cube3);
		// addChild(&cube4);
	}
	void draw()
	{
		// std::cout << "World draw \n";
		glEnable(GL_DEPTH_TEST);
		Scene::draw();
		glDisable(GL_DEPTH_TEST);
	}
};