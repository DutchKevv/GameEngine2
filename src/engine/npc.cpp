#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include "./npc.h"

Npc::Npc(string const &path, unsigned int amount, bool gamma) : Model(path, amount, gamma)
{
    Model(path, amount, gamma);
}

void Npc::setTown(Town *town) {
    this->town = town;
}

void Npc::init()
{
    Model::init();
}

void Npc::update(float delta)
{
    Model::update(delta);
}

void Npc::renderScene(float delta, Shader *shader, bool isShadowRender)
{
    if (amount == 1)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, this->scale);
        model = glm::translate(model, this->position);
        shader->setMat4("model", model);
    }
    else
    {
        for (int i = 0; i < amount; ++i)
        {
            glm::mat4 _model = modelMatrices[i];
            glm::mat4 model = glm::mat4(1.0f);
            Town *town = (Town*)this->scene->getChildById(this->town->warWith);

            if (town == NULL) {
                continue;
            }

            // std::cout << this->town->warWith;
            // model = glm::scale(model, this->scale);
            // model = glm::scale(model, this->scale);
            model = glm::translate(model, glm::vec3(_model[3][0] - (_model[3][0] - town->position.x) * speed, 1.0f, _model[3][2] - (_model[3][2] -  town->position.z) * speed));
            // model = glm::translate(model, glm::vec3(_model[3][0] - (_model[3][0] - scene->camera->Position.x) * speed, 1.0f, _model[3][2] - (_model[3][2] - scene->camera->Position.z) * speed));
            // model = glm::translate(model, glm::vec3(_model[3][0] - (_model[3][0] - scene->camera->Position.x) * speed, 1.0f, _model[3][2] - (_model[3][2] - scene->camera->Position.z) * speed));
            // model = glm::translate(model, glm::vec3(glfwGetTime() / 100000000000, 1.0f, 1.0f));
            modelMatrices[i] = model;
        }

        // glGenBuffers(1, &instanceBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
        glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
    }

    Model::renderScene(delta, shader, isShadowRender);
}