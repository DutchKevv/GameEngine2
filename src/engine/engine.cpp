#include "./engine.h"
unsigned int worldChild = 1;

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void Engine::init()
{
  context->engine = this;
  context->display = new Display();

  // context->resourceManager = new ResourceManager();

  context->display->init();
  context->display->createWindow();

  addModule(new GUI());

  //create the FBO
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glDrawBuffer(GL_COLOR_ATTACHMENT0);

  //create the texture and attach it to the fbo
  glGenTextures(1, &context->frameTexture);
  glBindTexture(GL_TEXTURE_2D, context->frameTexture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, context->display->windowW / 2, context->display->windowH / 2, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, context->frameTexture, 0);

  //DEPTH buffer
  glGenTextures(1, &depth_Texture);
  glBindTexture(GL_TEXTURE_2D, depth_Texture);

  // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, context->display->windowW, context->display->windowH, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, context->display->windowW / 2, context->display->windowH / 2, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_Texture, 0);

  //create the depth buffer attachment
  glGenRenderbuffers(1, &depthBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);

  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, context->display->windowW / 2, context->display->windowH / 2);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

  glBindFramebuffer(GL_FRAMEBUFFER, 0); //return to rendering to the normal fbo

  glfwSetCursorPosCallback(context->display->window, mouse_callback);
  // glfwSetScrollCallback(context->display->window, scroll_callback);

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    std::cout << "FRAMEBUFFER INCOMPLETE! \n";
  }

  // tell GLFW to capture our mouse
  // glfwSetInputMode(context->display->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // ImGui::SetNextWindowSize(ImVec2(context->display->windowW / 2, context->display->windowH / 2));
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  editor = new Editor();
  addScene(editor);
}

void Engine::start()
{
  double lasttime = glfwGetTime();

  // render loop
  // -----------
  while (!glfwWindowShouldClose(context->display->window))
  {

    // MAX FPS LOOP
    while (glfwGetTime() < lasttime + 1.0 / TARGET_FPS)
    {
      // TODO: Put the thread to sleep, yield, or simply do nothing
    }

    // per-frame time logic
    // --------------------
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lasttime += 1.0 / TARGET_FPS;
    lastFrame = currentFrame;

    // frame logic
    tick();
  }
}

// glfw: terminate, clearing all previously allocated GLFW resources.
// ------------------------------------------------------------------
void Engine::stop()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
}

void Engine::tick()
{
  glfwPollEvents();

  // input
  // -----
  processInput(context->display->window);

  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // ImGui::SetNextWindowSize(ImVec2(context->display->width / 2, context->display->height / 2));

  for (Module *module : modules)
  {
    module->beforeDraw();
  }

  for (Scene *child : children)
  {
    child->draw(deltaTime);
  }

  for (Module *module : modules)
  {
    module->afterDraw();
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // bool test = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);
  // std::cout << test;

  // ImGui::SetWindowFocus(NULL);

  glfwSwapBuffers(context->display->window);

  // this->renderer->handleInput();
  // this->renderer->update(deltaTime);
  // this->renderer->draw(deltaTime);
}

void Engine::addScene(Scene *scene)
{
  std::cout << "adding scene" << std::endl;

  children.push_back(scene);
  scene->init();
}

void Engine::addModule(Module *module)
{
  std::cout << "adding module: " + module->name << std::endl;

  modules.push_back(module);
  module->init();
}

// TODO
// get child dynamic (find the 'world' child)
void Engine::processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    children[worldChild]->camera->ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    children[worldChild]->camera->ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    children[worldChild]->camera->ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    children[worldChild]->camera->ProcessKeyboard(RIGHT, deltaTime);
}

// // glfw: whenever the mouse moves, this callback is called
// // -------------------------------------------------------
// // TODO
// // get child dynamic (find the 'world' child)
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
  Engine *engine = context->engine;

  if (engine->firstMouse)
  {
    engine->lastMouseX = xpos;
    engine->lastMouseY = ypos;
    engine->firstMouse = false;
  }

  float xoffset = xpos - engine->lastMouseX;
  float yoffset = engine->lastMouseY - ypos; // reversed since y-coordinates go from bottom to top

  engine->lastMouseX = xpos;
  engine->lastMouseY = ypos;

  context->engine->children[worldChild]->camera->ProcessMouseMovement(xoffset, yoffset);
}

// // glfw: whenever the mouse scroll wheel scrolls, this callback is called
// // ----------------------------------------------------------------------
// // TODO
// // get child dynamic (find the 'world' child)
// static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
// {
//   context->engine->children[worldChild]->camera->ProcessMouseScroll(yoffset);
// }