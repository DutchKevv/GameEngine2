#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>
#include <vector>

#include "./display.cpp"
// #include "./renderer.h"
#include "./scene.cpp"

void processInput(GLFWwindow *window);

class Engine
{
public:
  int TARGET_FPS = 60;
  Display *display;

  std::vector<Scene *> children;

  // Renderer *renderer;

  // timing
  float deltaTime = 0.0f; // time between current frame and last frame
  float lastFrame = 0.0f;

  void init()
  {
    // renderer = new Renderer();
    display = new Display();
    display->init();
    display->createWindow();
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
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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

private:
};

// process all input: query GLFW whether relevant keys are pressed/released
// this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}