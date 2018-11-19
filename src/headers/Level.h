#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "NLLinkedList.h"

using namespace sf;
using namespace std;

/*
You won't be able to fall out of the map, since the
flying would neglect the effect anyway. As far as entrances to levels and whatnot,
there's going to be doors on certain walls which will be indicated by a special
tile. To the user, this tile will be transparent, so it looks like there's nothing
there, but upon collision, the player will move to a new area.

*/
class Level {
private:

  const static int TILE_SIZE = 25;
  const static int VERTS_IN_QUAD = 4;

  // The background sprite for our level
  Sprite m_background;
  string m_backgroundPath;

  // We also have to have a tile sheet for the different blocks in the level
  string m_tileSheetPath;

  // Keep track of our level size
  Vector2i m_levelSize;

  // Where the player starts
  // Since there may be more than one entrance to the level, we need to create a
  // vector for each direction
  // It's ok that some of these won't be defined
  // It is important to note that the direction corresponding to coordinates will
  // be "opposite", as the direction implies the direction in the previous level.
  // ie. RIGHT will hold the coordinates when the player enters from the left,
  // because the player exited the previous level to the right
  map<Direction, Vector2f> m_startingLocation;

  // We will manage the tiles in the level through a vertex array
  VertexArray m_vertexArray;
  char** m_levelArray;

  // This will allow us to place the level in the map where it belongs
  string m_mapLocation;

public:
  Level(Vector2i levelSize, map<Direction, Vector2f> startingLocation, string backgroundPath,
     string tileSheetPath, VertexArray vArray, string mapLocation,
     char** arr);

  // We will never call this constructor for making our game, but it is used as
  // a control in the NLLinkedList class so we can compare values easily
  Level();

  static Level loadLevel(const string levelFilePath);

  // Some getters for drawing the level
  VertexArray getVertexArray(); // Done
  string getTileSheetPath(); // Done
  Vector2f getStartingLocation(Direction dir);
  map<Direction, Vector2f> getStartingLocations();
  string getMapLocation();
  Sprite getBackground();

  // We have to override the == operator because the NLLinkedlist class uses it
  // to identify whether two levels are the same
  bool operator==(Level compare);
  // This is solely used for comparing two levels
  char** getLevelArray();

  // A deconstructor to free up memory afterwords
  ~Level();

  // For debugging
  void printLevel();
};
