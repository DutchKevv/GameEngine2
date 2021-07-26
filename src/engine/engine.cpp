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
// #include "./texture.cpp"

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
  GLuint depthBuffer;
  GLuint depth_Texture;
  // Texture2D texture;

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

    //create the FBO
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    //create the texture and attach it to the fbo
    glGenTextures(1, &frameTexture);
    glBindTexture(GL_TEXTURE_2D, frameTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, context->display->width / 2, context->display->height / 2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexture, 0);

    //DEPTH buffer
    glGenTextures(1, &depth_Texture);
    glBindTexture(GL_TEXTURE_2D, depth_Texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, context->display->width / 2, context->display->height / 2, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_Texture, 0);

    //create the depth buffer attachment
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, context->display->width / 2, context->display->height / 2);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0); //return to rendering to the normal fbo

    glfwSetCursorPosCallback(context->display->window, mouse_callback);
    glfwSetScrollCallback(context->display->window, scroll_callback);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
      std::cout << "FRAMEBUFFER INCOMPLETE! \n";
    }

    // tell GLFW to capture our mouse
    // glfwSetInputMode(context->display->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2(context->display->height / 2, context->display->width / 2);
    ImGui_ImplGlfw_InitForOpenGL(context->display->window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    ImGui::SetNextWindowSize(ImVec2(context->display->width / 2, context->display->height / 2), ImGuiCond_FirstUseEver);
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
  void stop()
  {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
  }

  void tick()
  {
    glfwPollEvents();

    // input
    // -----
    processInput(context->display->window);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    for (Scene *child : children)
    {
      child->draw();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //create our ImGui window
    ImGui::Begin("Game");
    // ImGui::Begin("Game", NULL, ImGuiWindowFlags_NoFocusOnAppearing);

    //get the mouse position
    // ImGui::SetCursorPos(ImVec2(0, 0));
    ImVec2 pos = ImGui::GetCursorScreenPos();

    ImDrawList *drawList = ImGui::GetWindowDrawList();
    drawList->AddImage((void *)frameTexture, pos, ImVec2(pos.x + ImGui::GetWindowSize().x, pos.y + ImGui::GetWindowSize().y), ImVec2(0, 1), ImVec2(1, 0));

    // close window
    ImGui::End();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // bool test = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);
    // std::cout << test;

    ImGui::SetWindowFocus(NULL);

    glfwSwapBuffers(context->display->window);

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