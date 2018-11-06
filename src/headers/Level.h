#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
/*
You won't be able to fall out of the map, since the
flying would neglect the effect anyway. As far as entrances to levels and whatnot,
there's going to be doors on certain walls which will be indicated by a special
tile. To the user, this tile will be transparent, so it looks like there's nothing
there, but upon collision, the player will move to a new area.

TODO:
figure out how to link the levels together in the code, so the player can backtrack if they need to
*/
class Level {
private:

  // The background sprite for our level
  Sprite m_background;

  // We also have to have a tile sheet for the different blocks in the level
  Texture m_tileSheet;

  // We will manage the tiles in the level through a vertex array
  VertexArray m_vertexArray;
  int** m_levelArray = nullptr;

public:
  Level(Sprite background, Texture tileSheet, VertexArray vArray);
  static Level loadLevel(const string levelFilePath);

  // Some getters for drawing the level
  VertexArray getVertexArray();
  Texture getTileSheet();
};
