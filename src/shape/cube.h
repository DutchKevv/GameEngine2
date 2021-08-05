#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>

#include "../engine/logger.h"
#include "../engine/logger.h"
#include "../engine/renderObject.h"
#include "../engine/context.h"
#include "../engine/texture.h"
#include "../engine/resourceManager.h"
#include "../engine/shader.cpp"

class ShapeCube : public RenderObject
{

public:
  glm::vec3 color = glm::vec3(1.0f);
  bool loadTexture = true;

  unsigned int VBO;
  unsigned int cubeVAO;
  unsigned int EBO;

  glm::mat4 view;
  // Shader *shaderProgram;
  Texture2D *texture;

  void init();
  void draw(float delta);

  void renderScene(float delta, Shader *shader, bool isShadowRender);
};