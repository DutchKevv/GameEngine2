#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../engine/scene.cpp"
#include "../../shape/cube.cpp"

// const unsigned int SCR_WIDTH = 800;
// const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

class WorldScene : public Scene
{
public:
	ShapeCube *cube1 = new ShapeCube();
	ShapeCube *cube2 = new ShapeCube();
	ShapeCube *cube3 = new ShapeCube();
	ShapeCube *cube4 = new ShapeCube();

	void init()
	{
		// std::cout << "init world \n";

		cube1->position = glm::vec3(0.0f, 0.0f, 0.0f);
		cube2->position = glm::vec3(2.0f, 5.0f, -15.0f);
		cube3->position = glm::vec3(-1.5f, -2.2f, -2.5f);
		cube4->position = glm::vec3(-3.8f, -2.0f, -12.3f);

		addChild(cube1);
		addChild(cube2);
		addChild(cube3);
		addChild(cube4);
	}
	void draw()
	{
		// std::cout << "World draw \n";
		glm::mat4 view = camera->GetViewMatrix();
		cube1->shaderProgram->setMat4("view", view);
		cube2->shaderProgram->setMat4("view", view);

		glEnable(GL_DEPTH_TEST);
		Scene::draw();
		glDisable(GL_DEPTH_TEST);
	}
};