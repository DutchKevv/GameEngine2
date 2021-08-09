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

    void init();
    void update(float update);

    void renderScene(float delta, Shader *shader, bool isShadowRender);
};
