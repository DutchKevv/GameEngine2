#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <vector>

#include "./display.cpp"
#include "./resourceManager.cpp"
// #include "./renderer.h"
#include "./scene.cpp"
#include "./context.cpp"

// timing
float deltaTime = 0.0f; // time between current frame and last frame
bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

class Engine
{

public:
  int TARGET_FPS = 120;
  Display *display;

  std::vector<Scene *> children;

  // timing
  float deltaTime = 0.0f; // time between current frame and last frame
  float lastFrame = 0.0f;

  void init()
  {
    context->engine = this;
    // context->resourceManager = new ResourceManager();

    // renderer = new Renderer();
    display = new Display();
    display->init();
    display->createWindow();

    glfwSetCursorPosCallback(display->window, mouse_callback);
    glfwSetScrollCallback(display->window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(display->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }

  // render loop
  // -----------
  void start()
  {
    double lasttime = glfwGetTime();

    while (!glfwWindowShouldClose(display->window))
    {
      // per-frame time logic
      // --------------------
      float currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame;

      while (glfwGetTime() < lasttime + 1.0 / TARGET_FPS)
      {
        // TODO: Put the thread to sleep, yield, or simply do nothing
      }
      lasttime += 1.0 / TARGET_FPS;
      lastFrame = currentFrame;

      tick();
    }
  }

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  void stop() { glfwTerminate(); }

  void tick()
  {
    // input
    // -----
    processInput(display->window);

    // render
    // ------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (Scene *child : children)
    {
      child->draw();
    }

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse
    // moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(display->window);
    glfwPollEvents();

    // this->renderer->handleInput();
    // this->renderer->update(deltaTime);
    // this->renderer->draw(deltaTime);
  }

  void addScene(Scene *scene)
  {
    // std::cout << "adding scene \n";

    this->children.push_back(scene);
    scene->init();
  }

  void processInput(GLFWwindow *window)
  {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      children[0]->camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      children[0]->camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      children[0]->camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      children[0]->camera->ProcessKeyboard(RIGHT, deltaTime);
  }

  // glfw: whenever the mouse moves, this callback is called
  // -------------------------------------------------------
  static void mouse_callback(GLFWwindow *window, double xpos, double ypos)
  {
    if (firstMouse)
    {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    context->engine->children[0]->camera->ProcessMouseMovement(xoffset, yoffset);
  }

  // glfw: whenever the mouse scroll wheel scrolls, this callback is called
  // ----------------------------------------------------------------------
  static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
  {
    context->engine->children[0]->camera->ProcessMouseScroll(yoffset);
  }
};