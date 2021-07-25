#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include <glm/glm.hpp>

#include "../engine/logger.h"
#include "../engine/context.h"
#include "../engine/renderObject.cpp"
#include "../engine/shader.cpp"
#include "../shape/cube.cpp"

class Spotlight : public RenderObject
{

public:
	bool showCube = true;
	glm::vec3 lightColor = glm::vec3(0.2f, 0.3f, 0.6f);
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	Shader *shaderProgram;
	float translationX;
	float translationY;
	float translationZ;
	ShapeCube cube;

	void init()
	{
		shaderProgram = context->resourceManager->loadShader("light");

		if (showCube)
		{
			cube = ShapeCube();
			cube.loadTexture = false;
			cube.addChild(&cube, scene);
		}
	}

	void draw(float delta = 0.0)
	{
		translationX = 12.0f * cos(0.0f + 1.0f * (float)glfwGetTime());
		translationY = 1.0f;
		// translationY = 2.0f * sin(0.0f + 1.0f * (float)glfwGetTime());
		translationZ = 14.0f * sin(0.0f + 1.0f * (float)glfwGetTime());
		// glm::vec3 translation = glm::vec3(2.0f);
		glm::vec3 translation = glm::vec3(translationX, translationY, translationZ);

		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

		if (showCube)
		{
			cube.position = translation;
			cube.color = diffuseColor;
			cube.draw();
		}

		shaderProgram->use();
		// shaderProgram->setVec3("light.color", lightColor);
		shaderProgram->setVec3("light.position", translation);
		shaderProgram->setVec3("light.ambient", ambientColor);
		// shaderProgram->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		shaderProgram->setVec3("light.diffuse", diffuseColor); // darken diffuse light a bit
		// shaderProgram->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // darken diffuse light a bit
		shaderProgram->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	}
};