#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "../module.cpp"
#include "imgui.h"

class GUI : public Module
{
public:
    std::string name = "GUI";

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    void init();

    void beforeDraw();
};