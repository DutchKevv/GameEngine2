#pragma once

#include "./renderobject.h"
#include "./texture.h"

class Terrain2 : public RenderObject
{
public:
    Texture2D *texture;
    unsigned int VBO;
    unsigned int cubeVAO;
    unsigned int EBO;

    void init();

    void renderScene(float delta, Shader *shader, bool isShadowRender);

private:
    bool keyPressed = false;
};
