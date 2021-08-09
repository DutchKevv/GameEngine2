#include "./baseObject.h"

static unsigned int IDCounter = 0;

void BaseObject::init() {
	isInitialized = true;
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
			std::cout << "child draw \n";
			child->draw(delta);
		}
	}
}

void BaseObject::renderScene(float delta, Shader *shader, bool isShadowRender)
{
	if (shader)
	{
		shader->use();
	}

	for (BaseObject *child : children)
	{
		child->renderScene(delta, shader, isShadowRender);
	}
}

unsigned int BaseObject::addChild(BaseObject *child, Scene *scene, std::string name)
{
	child->id = IDCounter++;
	child->name = name;
	child->scene = scene;

	this->children.push_back(child);

	if (child->isInitialized == false)
	{
		child->init();
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
