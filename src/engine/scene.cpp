#pragma once
#include <iostream>
#include <string>

// #include "./renderobject.h"

class Scene
{
public:
  void init() {}

  void addObject() {}

  virtual void draw()
  {
    std::cout << "4444";
  }
};