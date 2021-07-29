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

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

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
  Texture2D texture;

  void init()
  {
    if (loadTexture)
    {
      texture = context->resourceManager->loadTexture("container2.jpg", true, "wall", 0, 0);
    }

    // shaderProgram = context->resourceManager->loadShader("shadow");
    // shaderProgram->use();

    // first, configure the cube's VAO (and VBO)
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // glUniform1i(glGetUniformLocation(shaderProgram->ID, "texture1"), 0);
  }

  void draw(float delta)
  {
    std::cout << "draw Cube \n";

    // const unsigned int SCR_WIDTH = 800;
    // const unsigned int SCR_HEIGHT = 600;

    // if (loadTexture)
    // {
    //   glActiveTexture(GL_TEXTURE0);
    //   texture.Bind();
    //   shaderProgram->setInt("useTextures", 1);
    // }
    // else
    // {
    //   glBindTexture(GL_TEXTURE_2D, 0);
    //   shaderProgram->setVec3("objectColor", color);
    //   shaderProgram->setInt("useTextures", 0);
    // }

    // // be sure to activate shader when setting uniforms/drawing objects
    // shaderProgram->use();

    // // glUniform1i(glGetUniformLocation(shaderProgram->ID, "texture1"), 0);

    // // shaderProgram->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    // shaderProgram->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    // shaderProgram->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    // shaderProgram->setVec3("material.specular", 0.0f, 0.0f, 0.0f);
    // shaderProgram->setFloat("material.shininess", 32.0f);

    // shaderProgram->setVec3("viewPos", scene->camera->Position);

    // view/projection transformations
    // glm::mat4 projection = glm::perspective(glm::radians(scene->camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    // glm::mat4 view = scene->camera->GetViewMatrix();
    // shaderProgram->setMat4("projection", projection);
    // shaderProgram->setMat4("view", view);

    // world transformation
    // glm::mat4 model = glm::mat4(1.0f);
    // shaderProgram->setMat4("model", glm::translate(model, position));

    // // render the cube
    // glBindVertexArray(cubeVAO);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  void renderScene(float delta, Shader *shader, bool isShadowRender)
  {
    // std::cout << "render cube \n";
    // shader->use();

    // // world transformation
    // glm::mat4 model = glm::mat4(1.0f);
    // shader->setMat4("model", glm::translate(model, position));

    // std::cout << "draw Cube \n";
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    if (loadTexture)
    {
      glActiveTexture(GL_TEXTURE0);
      texture.Bind();
      shader->setInt("useTextures", 1);
    }
    else
    {
      glBindTexture(GL_TEXTURE_2D, 0);
      shader->setVec3("objectColor", color);
      shader->setInt("useTextures", 0);
    }

    // be sure to activate shader when setting uniforms/drawing objects
    shader->use();

    glUniform1i(glGetUniformLocation(shader->ID, "texture1"), 0);

    shader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    shader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    shader->setVec3("material.specular", 0.0f, 0.0f, 0.0f);
    shader->setFloat("material.shininess", 32.0f);

    shader->setVec3("viewPos", scene->camera->Position);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(scene->camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = scene->camera->GetViewMatrix();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);


    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    shader->setMat4("model", glm::translate(model, position));

    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
};