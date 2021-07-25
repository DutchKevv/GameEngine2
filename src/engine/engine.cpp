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

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// timing
float deltaTime = 0.0f; // time between current frame and last frame
bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

class Engine
{

public:
  int TARGET_FPS = 120;
  unsigned int fbo;
  GLuint frameTexture;
  GLuint depthrenderbuffer;

  std::vector<Scene *> children;

  // timing
  float deltaTime = 0.0f; // time between current frame and last frame
  float lastFrame = 0.0f;

  void init()
  {
    context->engine = this;
    context->display = new Display();

    // context->resourceManager = new ResourceManager();

    // renderer = new Renderer();
    context->display->init();
    context->display->createWindow();

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    //Set up the texture to which we're going to render glGenTextures(1, &frameTexture);
    glBindTexture(GL_TEXTURE_2D, frameTexture);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexture, depthrenderbuffer);

    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

    glfwSetCursorPosCallback(context->display->window, mouse_callback);
    glfwSetScrollCallback(context->display->window, scroll_callback);

    // tell GLFW to capture our mouse
    // glfwSetInputMode(context->display->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(context->display->window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
  }

  // render loop
  // -----------
  void start()
  {
    double lasttime = glfwGetTime();

    while (!glfwWindowShouldClose(context->display->window))
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
    processInput(context->display->window);

    // render
    // ------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // std::cout << __cplusplus;
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (Scene *child : children)
    {
      child->draw();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    //create our ImGui window
    ImGui::Begin("Scene22 Window");

    //get the mouse position
    ImVec2 pos = ImGui::GetCursorScreenPos();

    // ImGui::Begin("Game Window");
    ImDrawList *drawList = ImGui::GetWindowDrawList();
    GLuint f_tex = context->engine->frameTexture;
    drawList->AddImage((void *)f_tex, pos, ImVec2(pos.x + 512, pos.y + 512), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse
    // moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(context->display->window);
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