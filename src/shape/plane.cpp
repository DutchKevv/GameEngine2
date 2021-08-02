#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>

#include "../engine/logger.h"
#include "../engine/logger.h"
#include "../engine/renderObject.cpp"
#include "../engine/context.h"
#include "../engine/texture.cpp"
#include "../engine/resourceManager.cpp"
#include "../engine/shader.cpp"

float planeVertices[] = {
    // positions          // normals           // texture coords
         1500.0f, -0.5f,  1500.0f,  0.0f, 1.0f, 0.0f,  1500.0f,  0.0f,
        -1500.0f, -0.5f,  1500.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -1500.0f, -0.5f, -1500.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1500.0f,

         1500.0f, -0.5f,  1500.0f,  0.0f, 1.0f, 0.0f,  1500.0f,  0.0f,
        -1500.0f, -0.5f, -1500.0f,  0.0f, 1.0f, 0.0f,   0.0f, 1500.0f,
         1500.0f, -0.5f, -1500.0f,  0.0f, 1.0f, 0.0f,  1500.0f, 1500.0f
};

class ShapePlane : public RenderObject
{

public:
  glm::vec3 color = glm::vec3(1.0f);
  bool loadTexture = true;

  unsigned int planeVBO;
  unsigned int planeVAO;
  unsigned int EBO;

  glm::mat4 view;
  Shader *shaderProgram;
  Texture2D *texture;

  void init()
  {
    if (loadTexture)
    {
      texture = context->resourceManager->loadTexture("grass.jpg", true, "grass2", 0, 0);
    }

    // plane VAO
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glBindVertexArray(0);

    // // first, configure the cube's VAO (and VBO)
    // glGenVertexArrays(1, &cubeVAO);
    // glGenBuffers(1, &VBO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    // glBindVertexArray(cubeVAO);

    // // position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);

    // // normal attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // // texture coord attribute
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);
    // // glUniform1i(glGetUniformLocation(shaderProgram->ID, "texture1"), 0);
  }

  void draw(float delta)
  {
    std::cout << "draw floor \n";
  }

  void renderScene(float delta, Shader *shader, bool isShadowRender)
  {
    // std::cout << "render floor \n";

    // glUniform1i(glGetUniformLocation(shader->ID, "texture1"), 0);
    shader->use();
    shader->setBool("useInstances", false);
    shader->setBool("useTexture", true);

    glActiveTexture(GL_TEXTURE0);
    texture->Bind();

    // shaderProgram->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    shader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
    shader->setFloat("material.shininess", 0.0f);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    // model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
    shader->setMat4("model", model);

    // render the cube
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }
};