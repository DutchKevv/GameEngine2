#include "./game/game.cpp"
#include <iostream>

int main()
{
  std::cout << "C++ version: " << __cplusplus << "\n";

  Game game;
  game.init();

  return 0;
}