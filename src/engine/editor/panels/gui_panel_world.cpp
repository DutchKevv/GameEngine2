#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"
#include "../../shader.cpp"
#include "../../renderObject.cpp"
#include "../../context.h"

class GuiPanelWorld : public RenderObject
{
public:
	void renderScene(float delta, Shader *shader, bool isShadowRender)
	{
		// std::cout << "rebder window";
		//create our ImGui window
		ImGui::Begin("Game2");
		// ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoFocusOnAppearing);

		//get the mouse position
		// ImGui::SetCursorPos(ImVec2(0, 0));
		ImVec2 pos = ImGui::GetCursorScreenPos();

		ImDrawList *drawList = ImGui::GetWindowDrawList();
		drawList->AddImage((void *)context->frameTexture, pos, ImVec2(pos.x + ImGui::GetWindowSize().x, pos.y + ImGui::GetWindowSize().y), ImVec2(0, 1), ImVec2(1, 0));

		// close window
		ImGui::End();
	}
};