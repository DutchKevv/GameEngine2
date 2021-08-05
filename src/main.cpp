#include "./game/game.h"
#include <iostream>

int main()
{
  std::cout << "C++ version: " << __cplusplus << "\n";

  Game game;
  game.init();

  return 0;
}