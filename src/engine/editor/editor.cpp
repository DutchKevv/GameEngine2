#pragma once

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"
#include "../scene.cpp"
#include "./panels/gui_panel_world.cpp"
// #include "../modules/gui/panels/gui_panel.cpp"

class Editor : public Scene
{
public:
	std::string name = "Root window";

	void init()
	{
		std::cout << "adding editor scene \n";

		addChild(new GuiPanelWorld(), this, "World");
	}

	void draw()
	{
		// std::cout << "drawing editor scene \n";

		Scene::draw();

		//create our ImGui window
		ImGui::Begin("Editor");
		// std::cout << __cplusplus;

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// ShowExampleMenuFile();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z"))
				{
				}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false))
				{
				} // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X"))
				{
				}
				if (ImGui::MenuItem("Copy", "CTRL+C"))
				{
				}
				if (ImGui::MenuItem("Paste", "CTRL+V"))
				{
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		// close window
		ImGui::End();
	}
};