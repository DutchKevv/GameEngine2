#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "./plane.h"
#include "../engine/context.h"

float planeVertices[] = {
    // positions          // normals           // texture coords
    1500.0f, -0.5f, 1500.0f, 0.0f, 1.0f, 0.0f, 1500.0f, 0.0f,
    -1500.0f, -0.5f, 1500.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -1500.0f, -0.5f, -1500.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1500.0f,

    1500.0f, -0.5f, 1500.0f, 0.0f, 1.0f, 0.0f, 1500.0f, 0.0f,
    -1500.0f, -0.5f, -1500.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1500.0f,
    1500.0f, -0.5f, -1500.0f, 0.0f, 1.0f, 0.0f, 1500.0f, 1500.0f};

  void ShapePlane::init()
  {
    if (loadTexture)
    {
      texture = context->resourceManager->loadTexture("sand.jpg", true, "grass2", 0, 0);
      // textureN = context->resourceManager->loadTexture("pbr/grass/ao.png", true, "grass2N", 0, 0);
    }

    // first, configure the cube's VAO (and VBO)
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glBindVertexArray(0);
  }

  void ShapePlane::draw(float delta)
  {
    std::cout << "draw floor \n";
  }

  void ShapePlane::renderScene(float delta, Shader *shader, bool isShadowRender)
  {
    // std::cout << "render floor \n";

    shader->use();
    shader->setBool("useInstances", false);
    shader->setBool("useTexture", true);
    shader->setBool("useNormal", false);
    shader->setInt("normalMap", 0);
    glActiveTexture(GL_TEXTURE0);
    texture->Bind();
    // glBindTexture(GL_TEXTURE_2D, texture->ID);
    // glActiveTexture(GL_TEXTURE2);
    // glBindTexture(GL_TEXTURE_2D, textureN->ID);
    // textureN->Bind();

    shader->setVec3("material.ambient", 0.3f,0.3f, 0.3f);
    shader->setInt("material.diffuse", 0);
    shader->setVec3("material.specular",0.0f, 0.0f, 0.0f);
    shader->setFloat("material.shininess", 8.0f);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, this->position);
    shader->setMat4("model", model);


    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);    

    // render the cube
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glCullFace(GL_BACK);  

    glActiveTexture(GL_TEXTURE0);
  }