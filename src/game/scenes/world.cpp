#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../engine/scene.cpp"
#include "../../engine/camera.h"
#include "../../shape/cube.cpp"
#include "../../shape/plane.cpp"
#include "../../lights/spotlight.cpp"
#include "../../shape/ui/gui.cpp"

class WorldScene : public Scene
{
public:
	ShapeCube *cube1;
	ShapeCube *cube2;
	ShapeCube *cube3;
	ShapeCube *cube4;
	ShapeCube *cube5;
	Spotlight *spotlight;
	ShapePlane *floor;
	GUI *gui;

	void init()
	{
		// std::cout << "init world \n";

		cube1 = new ShapeCube();
		cube2 = new ShapeCube();
		cube3 = new ShapeCube();
		cube4 = new ShapeCube();
		cube5 = new ShapeCube();
		spotlight = new Spotlight();
		floor = new ShapePlane();
		gui = new GUI();

		camera = new Camera(glm::vec3(0.0f, 10.0f, 20.0f));

		cube1->position = glm::vec3(0.0f, 0.0f, 0.0f);
		cube2->position = glm::vec3(2.0f, 0.0f, -15.0f);
		cube3->position = glm::vec3(-1.5f, 0.0f, -2.5f);
		cube4->position = glm::vec3(-3.8f, 0.0f, -12.3f);
		cube5->position = glm::vec3(0.0f, 0.0f, 0.0f);

		addChild(cube1, this);
		addChild(cube2, this);
		addChild(cube3, this);
		addChild(cube4, this);
		addChild(cube5, this);
		addChild(spotlight, this);
		addChild(floor, this);
		addChild(gui, this);
	}

	void draw()
	{
		glEnable(GL_DEPTH_TEST);
		Scene::draw();
		glDisable(GL_DEPTH_TEST);
	}
};