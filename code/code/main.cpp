#include <windows.h>

#include <iostream>

#include "Game.h"
int main() {
  SetConsoleCP(65001);
  SetConsoleOutputCP(65001);
  Game game;
  game.start();
  return 0;
}
