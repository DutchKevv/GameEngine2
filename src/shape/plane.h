#pragma once

#include <glm/glm.hpp>
#include "../engine/renderObject.h"
#include "../engine/texture.h"
#include "../engine/shader.h"

class ShapePlane : public RenderObject
{

public:
  bool loadTexture = true;

  void init();

  void renderScene(float delta, Shader *shader, bool isShadowRender);

private:
  unsigned int planeVBO;
  unsigned int planeVAO;
  unsigned int EBO;

  Texture2D *texture;
  Texture2D *textureN;
};