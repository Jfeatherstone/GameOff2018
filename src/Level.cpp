#include "headers/Level.h"
#include <SFML/Graphics.hpp>

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
  *m_levelArray = new int[1];
}

/*
Here is our actual constructor, which will be called in the static method
loadLevel()

First we want to assign our member variables to their new values
*/
Level::Level(Sprite background, Texture tileSheet, VertexArray vArray):
m_background(background), m_tileSheet(tileSheet), m_vertexArray(vArray) {

}

/*
We create a deconstructor to free up the memory taken by our level array once
we no longer need the object
*/
Level::~Level() {
  for (int i = 0; i < sizeof(m_levelArray[0])/sizeof(*m_levelArray[0]); i++) {
    delete[] m_levelArray[i];
  }
  delete[] m_levelArray;
}

VertexArray Level::getVertexArray() {
  return m_vertexArray;
}

int** Level::getLevelArray() {
  return m_levelArray;
}

Texture Level::getTileSheet() {
  return m_tileSheet;
}
