#pragma once

#include "./renderobject.h"
#include "./camera.h"
#include "./model.h"

class Player : public Model
{
public:
    Player(string const &path, unsigned int amount = 1, bool gamma = false);

    void init();
    
    void update(float update);

    void renderScene(float delta, Shader *shader, bool isShadowRender);

    int processKeyboard(Camera_Movement direction, float velocity);

private:
    bool keyPressed = false;
};
