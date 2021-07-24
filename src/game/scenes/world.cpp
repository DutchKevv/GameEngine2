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
		// std::cout << "init world \n";

		ShapeCube *cube1 = new ShapeCube();
		ShapeCube *cube2 = new ShapeCube();
		ShapeCube *cube3 = new ShapeCube();
		ShapeCube *cube4 = new ShapeCube();

		cube1->position = glm::vec3(0.0f, 0.0f, 0.0f);
		cube2->position = glm::vec3(2.0f, 5.0f, -15.0f);
		cube3->position = glm::vec3(-1.5f, -2.2f, -2.5f);
		cube4->position = glm::vec3(-3.8f, -2.0f, -12.3f);

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