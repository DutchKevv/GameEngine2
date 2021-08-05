#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "editor.h"
#include "../scene.h"
#include "./panels/gui_panel_world.h"

void Editor::init()
{
	std::cout << "adding editor scene \n";

	// GuiPanelWorld *test = new GuiPanelWorld();

	addChild(new GuiPanelWorld(), this, "World");
};

void Editor::draw(float delta)
{
	renderScene(delta, NULL, false);
};

void Editor::renderScene(float delta, Shader *shader, bool isShadowRender)
{

	// std::cout << "drawing editor scene \n";

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
};