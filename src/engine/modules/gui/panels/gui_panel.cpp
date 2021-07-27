#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
// #include "../../../context.h"

class GUIPanel : public RenderObject
{
public:
    std::string name = "";

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    void init()
    {
    }

    void draw(float delta = 0.0)
    {
        // // std::cout << __cplusplus;
        // // Start the Dear ImGui frame
        // ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        // ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        // if (show_demo_window)
        //     ImGui::ShowDemoWindow(&show_demo_window);

        // static float f = 0.0f;
        // static int counter = 0;

        // ImGui::Begin("Game Window");
        // ImVec2 pos = ImGui::GetCursorScreenPos();
        // ImDrawList *drawList = ImGui::GetWindowDrawList();
        // GLuint f_tex = context->engine->frameTexture;
        // drawList->AddImage((void *)f_tex, pos, ImVec2(pos.x + 512, pos.y + 512), ImVec2(0, 1), ImVec2(1, 0));
        // ImGui::End();
    }
};