#pragma once

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"
#include "../scene.cpp"
#include "./panels/gui_panel_world.cpp"

class Editor : public Scene
{
public:
	std::string name = "Root window";

	void init()
	{
		std::cout << "adding editor scene \n";

		addChild(new GuiPanelWorld(), this, "World");
	}

	void draw(float delta)
	{
		renderScene(delta, NULL, false);
	}

	void renderScene(float delta, Shader *shader, bool isShadowRender) {
		
		std::cout << "drawing editor scene \n";

		ImGui::Begin("Editor");

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

		Scene::renderScene(delta, shader, isShadowRender);
	}
};