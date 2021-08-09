#pragma once

#include "./camera.h"
#include "./renderobject.h"

class Scene : public RenderObject
{
public:
  Camera *camera;
};
