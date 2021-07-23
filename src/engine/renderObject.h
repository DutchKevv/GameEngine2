#pragma once

#include <vector>
#include "shader.h"
#include "baseObject.h"
#include "resourceManager.h"

class BaseObject;

class RenderObject : public BaseObject
{
public:
	std::vector<RenderObject *> children;

	unsigned int id;
	unsigned int width;
	unsigned int height;

	float speed;
	float xRadius = 0.0f;
	float yRadius = 0.0f;
	float yaw = 90;

	bool focused = false;

	glm::vec3 position = glm::vec3(1.0f);
	glm::vec3 rotation;

	RenderObject();
};