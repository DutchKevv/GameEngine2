#pragma once

#include <iostream>
#include <string>
#include "../scene.h"
#include "../shader.cpp"

class Editor : public Scene
{
public:
	std::string name = "Root window";

	void init();

	void draw(float delta);

	void renderScene(float delta, Shader *shader, bool isShadowRender);
};