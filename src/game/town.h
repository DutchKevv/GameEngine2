#pragma once

#include "../engine/engine.h"
#include "../engine/shader.h"
#include "../engine/model.h"
#include "../engine/renderObject.h"
#include <iostream>

class Town: public RenderObject
{
public:
    int warWith;
    Model * townModel;

	void init();
    void renderScene(float delta, Shader *shader, bool isShadowRender);
};