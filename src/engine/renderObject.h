#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include "./scene.h"
#include "./baseObject.h"

class RenderObject : public BaseObject
{
public:
	// Scene *scene;
	std::vector<RenderObject *> children;

	unsigned int id;
	unsigned int width;
	unsigned int height;

	float speed;
	float xRadius = 0.0f;
	float yRadius = 0.0f;
	float yaw = 90;

	bool focused = false;

	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1.0f);
	glm::vec3 position = glm::vec3(1.0f);

	RenderObject();
};