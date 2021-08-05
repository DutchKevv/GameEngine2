#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include <glm/glm.hpp>

#include "../engine/logger.h"
#include "../engine/context.h"
#include "../engine/renderObject.h"
#include "../engine/shader.cpp"
#include "../shape/cube.h"

class Spotlight : public RenderObject
{

public:
	bool showCube = false;
	glm::vec3 lightColor = glm::vec3(1.0f);

	float translationX;
	float translationY;
	float translationZ;
	ShapeCube cube;

	void init()
	{
		// if (showCube)
		// {
		// 	cube = ShapeCube();
		// 	cube.loadTexture = false;
		// 	cube.addChild(&cube, scene);
		// }
	}

	void draw(float delta)
	{
		std::cout << "draw light" << std::endl;
	}

	void renderScene(float delta, Shader *shader, bool isShadowRender)
	{
		// std::cout << "Render light" << std::endl;

		// glm::vec3 lightPos(-0.0f, 40.0f, -30.0f);

		float speed = 0.6f;
		// translationX = 0.0f;
		translationX = 120.0f * cos(0.0f + speed * (float)glfwGetTime());
		// translationY = 220.0f;
		translationY = 58.0f * sin(0.0f + speed * (float)glfwGetTime());
		// translationY = 2.0f * sin(0.0f + 1.0f * (float)glfwGetTime());
		// translationZ = scene->camera->Position.z - 150.0f;
		translationZ = -250.0f;
		// translationZ = -100.0f * sin(0.0f + speed * (float)glfwGetTime());
		// glm::vec3 translation = glm::vec3(2.0f);
		glm::vec3 translation = glm::vec3(translationX, translationY, translationZ);

		// if (translation.y < 2.0f) {
		// 	translation.y = 2.0f;
		// }
		position = translation;
		// position = lightPos;

		// lightColor.x = sin(glfwGetTime() * 1.0f);
		// lightColor.y = sin(glfwGetTime() * 0.7f);
		// lightColor.z = sin(glfwGetTime() * 1.3f);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.9f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

		if (showCube)
		{
			cube.position = translation;
			// cube.position = lightPos;
			cube.color = diffuseColor;
			cube.renderScene(delta, shader, isShadowRender);
		}

		shader->use();
		shader->setBool("useInstances", false);
		shader->setBool("useNormal", false);
		shader->setBool("useTexture", true);
		shader->setVec3("light.color", lightColor);
		// shader->setVec3("light.color", lightColor);
		// shader->setVec3("light.position", lightPos);
		shader->setVec3("light.position", translation);
		// shader->setVec3("light.ambient", ambientColor);
		shader->setVec3("light.ambient", ambientColor);
		// shader->setVec3("light.diffuse", lightColor); // darken diffuse light a bit
		// shader->setVec3("light.diffuse", lightColor); // darken diffuse light a bit
		shader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
		shader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	}
};