#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "imgui.h"

// settings
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

class Display
{
public:
	GLFWwindow *window;
	int width;
	int height;

	void init() {}

	int createWindow()
	{
		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// glfw window creation
		// --------------------
		// window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);

		// fullscreen
		const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		// window = glfwCreateWindow(800, 600, "Game Engine", glfwGetPrimaryMonitor(), NULL);
		window = glfwCreateWindow(mode->width, mode->height, "Game Engine", glfwGetPrimaryMonitor(), NULL);

		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// VSYNC
		glfwSwapInterval(1);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		glfwGetWindowSize(window, &width, &height);

		return 0;
	}
};

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width
	// and height will be significantly larger than specified on retina
	// displays.
	glViewport(0, 0, width, height);
}