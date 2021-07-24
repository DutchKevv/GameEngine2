#pragma once
#include <iostream>
#include <string>
#include <glm/glm.hpp>

#include "./renderobject.cpp"
#include "./camera.h"

class Scene : public RenderObject
{
public:
  Camera *camera;
};