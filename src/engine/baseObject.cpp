#include "baseObject.h"
#include "shader.h"

BaseObject::BaseObject()
{
}

void BaseObject::init()
{
}

void BaseObject::update(float delta)
{
	for (BaseObject *child : children)
	{
		if (child->isEnabled)
		{
			child->update(delta);
		}
	}
}

void BaseObject::draw(float delta)
{
	for (BaseObject *child : children)
	{
		if (child->isEnabled)
		{
			child->draw(delta);
		}
	}
}

void BaseObject::renderScene(float delta, Shader &shader, bool isShadowRender)
{
	for (BaseObject *child : children)
	{
		shader.Use();

		child->renderScene(delta, shader, isShadowRender);
	}
}

void BaseObject::destroy()
{
}