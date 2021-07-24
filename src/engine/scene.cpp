#pragma once
#include <iostream>
#include <string>
#include <glm/glm.hpp>

#include "./renderobject.cpp"
#include "./camera.h"

class Scene : public RenderObject
{
public:
  Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
};