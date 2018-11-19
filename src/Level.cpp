#include "headers/Level.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

bool Level::operator==(Level compare) {
  // This should properly differentiate between different levels while recognizing
  // identical ones
  if (getVertexArray().getBounds() == compare.getVertexArray().getBounds()) {
    // We say that if the level layout is exactly the same for the two,
    // the two levels are the same, as they shouldn't be the same otherwise
    if (getLevelArray() == compare.getLevelArray()) {
      return true;
    }
  }
  return false;
}

/*
Since this constructor is only used for comparing, we can leave most things
undefined, as it won't ever be used
*/
Level::Level() {
  //cout << "Level constructor" << endl;
  m_levelArray = new char*[1];
  m_levelArray[0] = new char[1];
}

/*
Here is our actual constructor, which will be called in the static method
loadLevel()

First we want to assign our member variables to their new values
Besides this, there isn't really much to do here
*/
Level::Level(Vector2i levelSize, map<Direction, Vector2f> startingLocation, Texture background,
   string tileSheet, VertexArray vArray, string mapLocation, char** arr):
 m_background(background), m_tileSheetPath(tileSheet), m_levelSize(levelSize),
m_startingLocation(startingLocation), m_vertexArray(vArray), m_levelArray(arr),
 m_mapLocation(mapLocation) {

}

/*
We create a deconstructor to free up the memory taken by our level array once
we no longer need the object

UPDATE: 11/19:
I think this is causing a seg fault at the end of execution, not quite sure why
If memory becomes a problem, I'll deal with this later
*/
Level::~Level() {
  /*
  for (int i = 0; i < sizeof(m_levelArray[0])/sizeof(*m_levelArray[0]); i++) {
    delete[] m_levelArray[i];
  }
  delete[] m_levelArray;
  */
}

VertexArray Level::getVertexArray() {
  return m_vertexArray;
}

char** Level::getLevelArray() {
  return m_levelArray;
}

string Level::getTileSheetPath() {
  return m_tileSheetPath;
}

string Level::getMapLocation() {
  return m_mapLocation;
}

Vector2f Level::getStartingLocation(Direction dir) {
  return m_startingLocation[dir];
}

map<Direction, Vector2f> Level::getStartingLocations() {
  return m_startingLocation;
}

void Level::printLevel() {
  cout << endl << "Map location: " << m_mapLocation << endl;
  cout << "Starting Locations: " << endl;
  for (auto element: m_startingLocation) {
    // The DIRECTION_NAMES array is found in NLLinkedList.h
    cout << DIRECTION_NAMES[element.first] << " (" << element.second.x << ", " << element.second.y << ")" << endl;
  }
  cout << "Level size: (" << m_levelSize.x << ", " << m_levelSize.y << ")" << endl;
  for (int y = 0; y < m_levelSize.y; y++) {
    for (int x = 0; x < m_levelSize.x; x++) {
      cout << m_levelArray[y][x];
    }
    cout << endl;
  }
  cout << endl;
}
