#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "imgui.h"
#include "display.h"
#include "context.h"

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void windowSizeCallback(GLFWwindow *window, int width, int height);

int Display::createWindow()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------

	// fullscreen
	if (fullscreen)
	{
		const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		window = glfwCreateWindow(mode->width, mode->height, "Game Engine", glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		window = glfwCreateWindow(1920, 1080, "Game Engine", NULL, NULL);
	}

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// VSYNC
	glfwSwapInterval(1);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// on window resize
	glfwGetWindowSize(window, &windowW, &windowH);
	// glfwSetWindowSizeCallback(context->window, windowSizeCallback);

	ratio = (float)context->display->windowW / (float)context->display->windowH;

	return 0;
}

// TEMP
// should be window size callback
void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	std::cout << "Resizing framebuffer" << std::endl;

	context->display->windowW = width;
	context->display->windowH = height;

	// make sure the viewport matches the new window dimensions; note that width
	// and height will be significantly larger than specified on retina
	// displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void windowSizeCallback(GLFWwindow *window, int width, int height)
{
	std::cout << "Resizing window" << std::endl;
	// context->engine->display->windowSize.width = width;
	// context->engine->display->windowSize.height = height;
}