#pragma once

#include "./renderobject.h"
#include "./camera.h"
#include "./model.h"

class Player : public RenderObject
{
public:
    Model *playerModel;

    void init();
    void update(float update);

    void renderScene(float delta, Shader *shader, bool isShadowRender);
    
    int processKeyboard(Camera_Movement direction, float velocity);

    float yM = 0.0f;
    const float minSpeed = -0.1f;
    const float maxSpeed = 0.1f;
    const float airborneThreshold = 0.01f;
    bool isAirborne = false;

private:
    bool keyPressed = false;
};
