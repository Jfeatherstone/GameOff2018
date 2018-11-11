// Our compile command using g++:
// g++ -o Main src/*.cpp -lsfml-system -lsfml-window -lsfml-graphics -lsfml-sound

#include "headers/Engine.h"
#include <iostream>

int main() {
  //Engine engine;
  //engine.run();
  Level level = *Level::loadLevel("levels/level1.txt");

  level.printLevel();

  return 0;
}
