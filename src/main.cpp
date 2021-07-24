#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

#include "./game/game.cpp"
#include "./engine/context.h"

int main()
{
  // std::cout << __cplusplus;

  Game game;
  game.init();

  return 0;
}