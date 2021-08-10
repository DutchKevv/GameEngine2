#pragma once

#include <vector>
#include <string>
#include "./shader.h"
// #include "./scene.h"

class Scene;

class BaseObject
{

public:
	unsigned int id;
	std::string name;
	Scene *scene;
	std::vector<BaseObject *> children;

	bool isInitialized = false;
	bool isEnabled = true;
	bool isVisible = true;

	virtual void init();

	virtual void update(float delta);

	virtual void draw(float delta);

	virtual void renderScene(float delta, Shader *shader, bool isShadowRender);

	unsigned int addChild(BaseObject *child, Scene *scene, std::string name = "");

	BaseObject *getChildByName(std::string name);

	BaseObject *getChildById(int id);

	template <class T>
	BaseObject *getChildByClass()
	{
		for (BaseObject *child : children)
		{
			if (T *v = dynamic_cast<T *>(child))
			{
				// old was safely casted to NewType
				return child;
			}
		}

		return NULL;
	};
};
