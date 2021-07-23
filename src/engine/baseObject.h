#pragma once

#include <vector>
#include "shader.h"
#include "logger.h"
#include "resourceManager.h"

static unsigned int IDCounter = 0;

class BaseObject
{

public:
	std::vector<BaseObject *> children;

	bool isInitialized = false;
	bool isEnabled = true;
	bool isVisible = true;

	unsigned int id;
	string name;

	BaseObject();

	virtual void init();

	virtual void update(float delta);

	virtual void draw(float delta);

	virtual void renderScene(float delta, Shader &shader, bool isShadowRender);

	virtual void destroy();

	int addChild(BaseObject *child, string name = "")
	{
		child->id = IDCounter++;
		child->name = name;

		this->children.push_back(child);

		if (child->isInitialized == false)
		{
			child->init();
			child->isInitialized = true;
		}

		return child->id;
	};

	BaseObject *getChildByName(string name)
	{
		for (BaseObject *child : children)
		{
			if (child->name == name)
			{
				return child;
			}
		}
	}

	BaseObject *getChildById(int id)
	{
		for (BaseObject *child : children)
		{
			if (child->id == id)
			{
				return child;
			}
		}
	}
};