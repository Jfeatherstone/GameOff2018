// Our compile command using g++:
// g++ -std=c++17 -o Main src/*.cpp -lsfml-system -lsfml-window -lsfml-graphics -lstdc++fs

#include "headers/Engine.h"
#include <iostream>

using namespace std;


int main() {
  Engine engine;
  engine.run();
  /*
  cout << "Before level" << endl;
  cout << "After level" << endl;
  Level loaded = Level::loadLevel("levels/level1.txt");
  loaded.printLevel();

  cout << "After load" << endl;
  NLLinkedList<Level> list;
  list.setOrigin(loaded);
  cout << "after list" << endl;
  list.getOrigin().printLevel();
  */
  cout << "Done!" << endl;
  return 0;
}
