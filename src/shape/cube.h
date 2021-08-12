#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../engine/renderObject.h"
#include "../engine/texture.h"
#include "../engine/shader.h"

class ShapeCube : public RenderObject
{

public:
  bool loadTexture = true;

  void init();

  void renderScene(float delta, Shader *shader, bool isShadowRender);

private:
  Texture2D *texture;

  GLuint VBO;
  GLuint VAO;
  GLuint EBO;
};