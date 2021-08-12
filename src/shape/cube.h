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
#include "../engine/shader.h"

class ShapeCube : public RenderObject
{

public:
  bool loadTexture = true;

  void init();

  void renderScene(float delta, Shader *shader, bool isShadowRender);

private:
  Texture2D *texture;

  unsigned int VBO;
  unsigned int cubeVAO;
  unsigned int EBO;
};