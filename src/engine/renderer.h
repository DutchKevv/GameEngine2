#pragma once

// #include "./opengl_headers.h"

// #include <STB/stb_image.h>
#include <vector>

#include "logger.h"
#include "renderObject.h"
#include "spriteRenderer.h"
#include "camera.h"
#include "scene.h"

class Renderer : public RenderObject
{

public:
	GLFWwindow *window;

	SpriteRenderer *sprite;

	void initSpriteHandler();

	void createWindow();
	void resizeWindow(int width, int height);
	void changeResolution(int width, int height);
	void destroyWindow();

	void init();

	void handleInput();
	void update(float delta);
	void draw(float delta);

	void destroy();
};