#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Display
{
public:
	GLFWwindow *window;

	int screenW;
	int screenH;
	int windowW;
	int windowH;

	float ratio = 1.0f;

	bool fullscreen = true;

	void init() {}

	int createWindow();
};
