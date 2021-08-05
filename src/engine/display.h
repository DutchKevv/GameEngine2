#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui.h"
#include "context.h"

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

// void framebufferSizeCallback(GLFWwindow *window, int width, int height)
// {
// 	std::cout << "Resizing framebuffer" << std::endl;

// 	context->display->windowW = width;
// 	context->display->windowH = height;

// 	// make sure the viewport matches the new window dimensions; note that width
// 	// and height will be significantly larger than specified on retina
// 	// displays.
// 	glViewport(0, 0, width, height);
// }