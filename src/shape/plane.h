#pragma once

#include <glm/glm.hpp>
#include "../engine/renderObject.h"
#include "../engine/texture.h"
#include "../engine/shader.cpp"

class ShapePlane : public RenderObject
{

public:
  glm::vec3 position = glm::vec3(0.0f);

  bool loadTexture = true;

  void init();

  void draw(float delta);

  void renderScene(float delta, Shader *shader, bool isShadowRender);

private:
  unsigned int planeVBO;
  unsigned int planeVAO;
  unsigned int EBO;

  Texture2D *texture;
  Texture2D *textureN;
};