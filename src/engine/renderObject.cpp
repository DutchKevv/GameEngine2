#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "./baseObject.cpp"

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

	glm::vec3 rotation;

	virtual void draw(float delta)
	{
		BaseObject::draw(delta);
	}

	// void renderScene(float delta, Shader *shader, bool isShadowRender)
	// {
	// 	BaseObject::renderScene(delta, shader, isShadowRender);
	// }
};