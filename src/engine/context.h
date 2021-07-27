#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "./engine.cpp"
#include "./resourceManager.cpp"
#include "./display.cpp"
// #include "./renderer.cpp"

class Engine;
class ResourceManager;
class Display;

struct CursorBehavior
{
	int GE_CURSOR_HIDDEN = 1;
};

struct MouseState
{
	bool firstMouse = true;
	bool active = true;
	float lastX = 0;
	float lastY = 0;
	float offsetX = 0;
	float offsetY = 0;
};

struct ScrollState
{
	bool active = false;
	double offsetX = 0;
	double offsetY = 0;
};

struct Paths
{
	std::string cwd = "";
};

struct Context
{

	// Context();

	Engine *engine;
	ResourceManager *resourceManager;
	Display *display;
	// Renderer *renderer;
	GLFWwindow *window;

	unsigned int fbo;
	GLuint frameTexture;

	struct GLFWOpenGLWindowInternalData *m_data;

	Paths *paths = new Paths();

	int type;
	bool fullscreen = false;
	int windowW = 800;
	int windowH = 600;
	int resolutionW = 600;
	int resolutionH = 600;
	int dayCycle;
	int dayCycleMax = 5000;

	MouseState *mouse = new MouseState;
	ScrollState *scroll = new ScrollState;

	GLuint cursorBehavior = GLFW_CURSOR_DISABLED;
	// GLuint cursorBehavior = GLFW_CURSOR_HIDDEN;

	float mouseLastX;
	float mouseLastY;
	bool firstMouse;
};

// extern CursorBehavior *CursorBehavior;
extern Context *context;