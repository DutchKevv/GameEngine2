#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "./baseObject.cpp"
#include "./scene.cpp"
#include "./camera.h"
#include "./scene.cpp"

class RenderObject : public BaseObject
{
public:
	// Scene *scene;
	std::vector<RenderObject *> children;
	// Camera *camera;

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

	virtual void draw()
	{
		BaseObject::draw();
	}
};