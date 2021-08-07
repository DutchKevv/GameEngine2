#pragma once
#include <vector>
#include <string>
#include "./shader.cpp"
// #include "./scene.h"

class Scene;

class BaseObject
{

public:
	Scene *scene;
	std::vector<BaseObject *> children;

	bool isInitialized = false;
	bool isEnabled = true;
	bool isVisible = true;

	unsigned int id;

	std::string name;

	virtual void init()
	{
	}

	virtual void update(float delta)
	{
		for (BaseObject *child : children)
		{
			if (child->isEnabled)
			{
				child->update(delta);
			}
		}
	}

	virtual void draw(float delta)
	{
		for (BaseObject *child : children)
		{
			if (child->isEnabled)
			{
				std::cout << "child draw \n";
				child->draw(delta);
			}
		}
	}

	virtual void renderScene(float delta, Shader *shader, bool isShadowRender)
	{
		if (shader)
		{
			shader->use();
		}

		for (BaseObject *child : children)
		{
			if (shader)
			{
				shader->setBool("useInstances", false);
				shader->setBool("useTexture", true);
				// glBindTexture(GL_TEXTURE_2D, 0);
			}

			child->renderScene(delta, shader, isShadowRender);
		}
	}

	virtual void destroy()
	{
	}

	int addChild(BaseObject *child, Scene *scene, std::string name = "");

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
