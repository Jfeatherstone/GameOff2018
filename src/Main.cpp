// Our compile command using g++:
// g++ -o Main src/*.cpp -lsfml-system -lsfml-window -lsfml-graphics

#include "headers/Engine.h"
#include <iostream>
//#include <SFML/Graphics.hpp>
#include "headers/NLLinkedList.h"

using namespace std;


int main() {
  cout << "Before method" << endl;
  //Engine engine;
  //engine.run();

  cout << "Before level" << endl;
  cout << "After level" << endl;
  Level loaded = Level::loadLevel("levels/level1.txt");
  loaded.printLevel();

  cout << "After load" << endl;
  NLLinkedList<Level> list;
  list.setOrigin(loaded);
  cout << "after list" << endl;
  list.getOrigin().printLevel();
  
  cout << "Done!" << endl;
  return 0;
}
