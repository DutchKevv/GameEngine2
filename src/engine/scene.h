#pragma once
#include "./renderobject.h"
#include "./camera.h"

class Scene : public RenderObject
{
public:
  Camera *camera;
  Scene();
};
