#pragma once

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"
#include "../../shader.h"
#include "../../scene.h"
#include "../../renderObject.h"
#include "../../engine.h"
#include "../../context.h"

using namespace std;

class GuiPanelCamera : public RenderObject
{
public:
	void renderScene(float delta, Shader *shader, bool isShadowRender)
	{
		ImGuiTableFlags flags = ImGuiTableFlags_Resizable + ImGuiTableFlags_Borders;
		// std::cout << "rebder window";
		//create our ImGui window
		ImGui::Begin("Camera");
		ImGui::SetWindowFontScale(2.8);
		// ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoFocusOnAppearing);

		//get the mouse position
		// ImGui::SetCursorPos(ImVec2(0, 0));
		ImVec2 pos = ImGui::GetCursorScreenPos();
		// ImGui::Text("Position :", context->engine->children[1]->camera->Position.x);
		ImGui::Text("Up :");
		ImGui::Text("Down :");
		// close window
		ImGui::End();
	}
};