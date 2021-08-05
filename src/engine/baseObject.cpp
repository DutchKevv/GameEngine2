#include <vector>
#include <string>
#include "./baseObject.h"
#include "./shader.cpp"
#include "./scene.h"

static unsigned int IDCounter = 0;

int BaseObject::addChild(BaseObject *child, Scene *scene, std::string name)
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

BaseObject *BaseObject::getChildByName(std::string name)
{
	for (BaseObject *child : children)
	{
		if (child->name == name)
		{
			return child;
		}
	}

	return NULL;
};

BaseObject *BaseObject::getChildById(int id)
{
	for (BaseObject *child : children)
	{
		if (child->id == id)
		{
			return child;
		}
	}

	return NULL;
};

template <class T>
BaseObject *BaseObject::getChildByClass()
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
