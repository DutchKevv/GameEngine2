#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h> /* defines FILENAME_MAX */

#include <iostream>

#include "../helpers/shader-loader.cpp"
#include "../helpers/shader.cpp"
#include "../helpers/texture.cpp"
// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

class ShapeTriangle {
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;

   public:
    Shader *shaderProgram;
    Texture *texture;
    void init() {
        float vertices[] = {
            // positions          // colors           // texture coords
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // top left
        };
        unsigned int indices[] = {
            // note that we start from 0!
            0, 1, 3,  // first triangle
            1, 2, 3   // second triangle
        };
        ShaderLoader shaderLoader;
        texture = new Texture("wall.jpg");
        shaderProgram = shaderLoader.load("triangle");
        shaderProgram->use();

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s),
        // and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                     GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        // note that this is allowed, the call to glVertexAttribPointer registered
        // VBO as the vertex attribute's bound vertex buffer object so afterwards we
        // can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // remember: do NOT unbind the EBO while a VAO is active as the bound
        // element buffer object IS stored in the VAO; keep the EBO bound.
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally
        // modify this VAO, but this rarely happens. Modifying other VAOs requires a
        // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
        // VBOs) when it's not directly necessary.
        glBindVertexArray(0);
        glUniform1i(glGetUniformLocation(shaderProgram->ID, "ourTexture"), 0);
        // uncomment this call to draw in wireframe polygons.
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void draw() {
        // draw our first triangle
        glUseProgram(shaderProgram->ID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
};