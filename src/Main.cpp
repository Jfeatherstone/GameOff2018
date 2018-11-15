// Our compile command using g++:
// g++ -o Main src/*.cpp -lsfml-system -lsfml-window -lsfml-graphics

#include "headers/Engine.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "headers/Level.h"
#include "headers/NLLinkedList.h"

using namespace std;


int main() {
  cout << "Before method" << endl;
  //Engine engine;
  //engine.run();

  /*
  // Testing levels and reading them in
  Level level = *Level::loadLevel("levels/level1.txt");

  level.printLevel();

  Texture texture = TextureHolder::getTexture("graphics/background.png");
  */
  cout << "Before level" << endl;
  Level level;
  cout << "After level" << endl;
  Level loaded = Level::loadLevel("levels/level1.txt");
  loaded.printLevel();
  loaded.printLevel();
  cout << "After load" << endl;
  NLLinkedList<Level> list;
  cout << "after list" << endl;


  cout << "Done!" << endl;
  return 0;
}
