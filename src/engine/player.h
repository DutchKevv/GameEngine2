#pragma once

#include "./renderobject.h"
#include "./animation.h"
#include "./animator.h"
#include "./camera.h"
#include "./model.h"

class Player : public RenderObject
{
public:
    Animation *danceAnimation;
    Animator *animator;

    Model *playerModel;

    // int speed = 0.001f;

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
