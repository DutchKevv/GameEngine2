#pragma once

#include "./renderobject.h"
#include "./camera.h"
#include "./model.h"

class Player : public RenderObject
{
public:
	// Animation *danceAnimation;
	// Animator *animator;
    
    Model *playerModel;

    void init();

    void renderScene(float delta, Shader *shader, bool isShadowRender);
};
