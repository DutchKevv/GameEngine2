#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "./gui.h"
#include "../../context.h"
#include "../module.cpp"

void GUI::init()
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
    style->WindowMinSize = ImVec2(800, 600);

    // ImGui::SetWindowFontScale(1.8);
};

void GUI::beforeDraw()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
};