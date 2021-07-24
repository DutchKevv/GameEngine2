#include <vector>
#include <string>
#include "../helpers/shader.cpp"

static unsigned int IDCounter = 0;

class BaseObject
{
public:
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

	virtual void draw(float delta = 0.0)
	{
		// std::cout << "Base draw \n";
		for (BaseObject *child : children)
		{
			if (child->isEnabled)
			{
				std::cout << "child draw \n";
				child->draw();
			}
		}
	}

	void renderScene(float delta, Shader &shader, bool isShadowRender)
	{
		for (BaseObject *child : children)
		{
			shader.use();

			child->renderScene(delta, shader, isShadowRender);
		}
	}

	virtual void destroy()
	{
	}

	int addChild(BaseObject *child, std::string name = "")
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
};
