#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "./baseObject.h"

class RenderObject : public BaseObject
{
public:
	std::vector<RenderObject *> children;

	unsigned int width;
	unsigned int height;

	float speed = 0.001f;
	float xRadius = 0.0f;
	float yRadius = 0.0f;
	float yaw = 90;

	bool focused = false;

	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 rotation = glm::vec3(1.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::vec3 position = glm::vec3(1.0f);
	
 	glm::vec3 color = glm::vec3(1.0f);
};