#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "../../context.h"
#include "../module.cpp"

class GUI : public Module
{
public:
    std::string name = "GUI";

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    void init()
    {
        // ImGui setup
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        // io.DisplaySize = ImVec2(context->display->windowW / 2, context->display->windowH / 2);

        // ImGui init
        ImGui_ImplGlfw_InitForOpenGL(context->display->window, true);
        ImGui_ImplOpenGL3_Init("#version 130");

        // ImGui style
        ImGui::StyleColorsDark();
        ImGuiStyle *style = &ImGui::GetStyle();
        style->WindowMinSize = ImVec2(320, 320);
    }

    void beforeDraw()
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
};