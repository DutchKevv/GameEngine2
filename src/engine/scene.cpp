#pragma once
#include <iostream>
#include <string>

#include "./renderobject.h"

class Scene : public RenderObject
{
public:
  virtual void init() {}

  void addObject() {}

  virtual void draw()
  {
  }
};