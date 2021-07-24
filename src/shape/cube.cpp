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

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
unsigned int VBO, cubeVAO;
unsigned int lightCubeVAO;
class ShapeCube : public RenderObject
{

public:
  unsigned int VBO;
  unsigned int VAO;
  unsigned int EBO;

  glm::mat4 view;
  Shader *shaderProgram;
  Texture2D texture;
  float translationX;
  float translationY;
  float translationZ;

  void init()
  {
    // ShaderLoader shaderLoader;
    texture = context->resourceManager->LoadTexture("wall.jpg", true, "wall", 0, 0);
    shaderProgram = context->resourceManager->loadShader("light");
    shaderProgram->use();

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
    glUniform1i(glGetUniformLocation(shaderProgram->ID, "texture1"), 0);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(2);
  }

  void draw(float delta = 0.0)
  {
    translationX = 12.0f * cos(0.0f + 3.0f * (float)glfwGetTime());
    translationY = 2.0f * sin(0.0f + 3.0f * (float)glfwGetTime());
    translationZ = 14.0f * sin(0.0f + 3.0f * (float)glfwGetTime());

    // std::cout << "draw Cube \n";
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    // be sure to activate shader when setting uniforms/drawing objects
    shaderProgram->use();
    shaderProgram->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    // shaderProgram->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    // shaderProgram->setVec3("lightPos", glm::vec3(translationX, translationY, translationZ));
    // shaderProgram->setVec3("lightPos", lightPos);
    shaderProgram->setVec3("viewPos", scene->camera->Position);
    glUniform1i(glGetUniformLocation(shaderProgram->ID, "texture1"), 0);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(scene->camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = scene->camera->GetViewMatrix();
    shaderProgram->setMat4("projection", projection);
    shaderProgram->setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    shaderProgram->setMat4("model", glm::translate(model, position));

    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // // also draw the lamp object
    // shaderProgram->use();
    // shaderProgram->setMat4("projection", projection);
    // shaderProgram->setMat4("view", view);
    // float translation = 1.0f * cos(0.0f + 1.0f * (float)glfwGetTime());
    // model = glm::mat4(1.0f);
    // // model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    // model = glm::translate(model, glm::vec3(translationX, translationY, translationZ));
    // model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    // shaderProgram->setMat4("model", model);

    // glBindVertexArray(lightCubeVAO);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
  }
};