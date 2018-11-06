// Our compile command using g++:
// g++ -o Main src/*.cpp -lsfml-system -lsfml-window -lsfml-graphics -lsfml-sound

#include "headers/Engine.h"

int main() {
  Engine engine;

  engine.run();

  return 0;
}
