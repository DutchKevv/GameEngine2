#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"

#include "../modules/gui/panels/gui_panel.cpp"
#include "../scene.cpp"
#include "../camera.h"

class Editor : public Scene
{
public:
	std::string name = "Root window";

	void init()
	{
		// std::cout << "adding editor scene \n";

		// std::cout << __cplusplus;
	}

	void draw()
	{
		// std::cout << "drawing editor scene \n";

		// Start the Dear ImGui frame
		// ImGui_ImplOpenGL3_NewFrame();
		// ImGui_ImplGlfw_NewFrame();
		// ImGui::NewFrame();

		// static float f = 0.0f;
		// static int counter = 0;

		ImGui::Begin("Main Window");

		ImGui::End();
	}
};