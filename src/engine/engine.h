#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "./scene.h"
#include "./editor/editor.h"
#include "./modules/module.cpp"
#include "./modules/gui/gui.h"

class Engine
{

public:
  std::vector<Module *> modules;
  std::vector<Scene *> children;
  GUI *gui;

  int TARGET_FPS = 60;

  unsigned int fbo;

  GLuint depthBuffer;
  GLuint depth_Texture;

  float lastMouseX = 0.5f;
  float lastMouseY = 0.5f;
  bool firstMouse = true;
  unsigned int worldChild = 1;

  // timing
  float deltaTime = 0.0f; // time between current frame and last frame
  float lastFrame = 0.0f;

  Editor *editor;

  void init();
  void start();
  void stop();
  void tick();
  void addScene(Scene *scene);
  void addModule(Module *module);
  void processInput(GLFWwindow *window);

  // static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
  // {
  //   context->engine->children[worldChild]->camera->ProcessMouseScroll(yoffset);
  // };
};