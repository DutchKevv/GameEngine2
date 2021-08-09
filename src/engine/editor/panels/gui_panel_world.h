#pragma once
#include "../../renderObject.h"
#include "../../shader.h"

class GuiPanelWorld : public RenderObject
{
public:
	void renderScene(float delta, Shader *shader, bool isShadowRender);
};