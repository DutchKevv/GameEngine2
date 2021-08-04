#pragma once
#include <vector>
#include <string>
#include "./shader.cpp"
#include "./scene.cpp"

class Scene;

static unsigned int IDCounter = 0;

class BaseObject
{

public:
	Scene *scene;
	std::vector<BaseObject *> children;
	glm::vec3 position = glm::vec3(1.0f);

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
			if (shader) {
				shader->setBool("useInstances", false);
				shader->setBool("useTexture", 1);
			}

			child->renderScene(delta, shader, isShadowRender);
		}
	}

	virtual void destroy()
	{
	}

	int addChild(BaseObject *child, Scene *scene, std::string name = "")
	{
		child->id = IDCounter++;
		child->name = name;
		child->scene = scene;

		this->children.push_back(child);

		if (child->isInitialized == false)
		{
			child->init();
			child->isInitialized = true;
		}

		return child->id;
	};

	BaseObject *getChildByName(std::string name)
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
	}
};
