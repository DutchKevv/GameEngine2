#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #include <iostream>
#include <vector>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// #include "./display.cpp"
// #include "./resourceManager.cpp"
#include "./scene.h"
#include "./context.h"
#include "./editor/editor.h"
#include "./modules/module.cpp"
#include "./modules/gui/gui.h"

class Engine
{

public:
  std::vector<Module *> modules;
  std::vector<Scene *> children;

  GUI *gui;

  int TARGET_FPS = 120;

  unsigned int fbo;
  // GLuint frameTexture;
  GLuint depthBuffer;
  GLuint depth_Texture;

  // float lastX = SCR_WIDTH / 2.0f;
  // float lastY = SCR_HEIGHT / 2.0f;
  float lastMouseX = 0.5f;
  float lastMouseY = 0.5f;
  bool firstMouse = true;

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
  // static void mouse_callback(GLFWwindow *window, double xpos, double ypos)
  // {
  //   Engine *engine = context->engine;

  //   if (engine->firstMouse)
  //   {
  //     engine->lastMouseX = xpos;
  //     engine->lastMouseY = ypos;
  //     engine->firstMouse = false;
  //   }

  //   float xoffset = xpos - engine->lastMouseX;
  //   float yoffset = engine->lastMouseY - ypos; // reversed since y-coordinates go from bottom to top

  //   engine->lastMouseX = xpos;
  //   engine->lastMouseY = ypos;

  //   context->engine->children[worldChild]->camera->ProcessMouseMovement(xoffset, yoffset);
  // };
  // static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
  // {
  //   context->engine->children[worldChild]->camera->ProcessMouseScroll(yoffset);
  // };
};