#include "headers/Level.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

bool contains(char arr[], char c);

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
Level::Level(Vector2i levelSize, map<Direction, Vector2f> startingLocation, string backgroundPath,
   string tileSheet, VertexArray vArray, string mapLocation, char** arr):
  m_tileSheetPath(tileSheet), m_levelSize(levelSize),
m_startingLocation(startingLocation), m_vertexArray(vArray), m_levelArray(arr),
 m_mapLocation(mapLocation) {
   m_backgroundPath = backgroundPath;
   m_background.setTexture(TextureHolder::getTexture(backgroundPath));
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

/*
This is defined is this class because I don't want to deal with the nightmare of
try to pass our two dimensional array for the level
*/
void Level::detectCollision(PlayableCharacter &character) {

  // Since we don't want to check every single block in the level, we create a
  // smaller zone around the players current location
  FloatRect detectionZone = character.getPosition();
  // Since our character has it center set at the center of the sprite, we have
  // to account for that when we check collisions
  detectionZone.left += detectionZone.width / 2;
  detectionZone.top += detectionZone.height / 2;

  // This will be assigned for each block as we iterate through the level
  FloatRect block;
  block.width = TILE_SIZE;
  block.height = TILE_SIZE;

  // Get the starting coordinates for our detection zone, adding some padding
  // We divide y tile size because this isn't the location on the screen,
  // but the location in the array
  Vector2f start;
  start.x = (int)(detectionZone.left / TILE_SIZE) - 1; // check and extra 1 to the left
  start.y = (int)(detectionZone.top / TILE_SIZE) - 1;

  // Where we should stop checking
  Vector2f end;
  end.x = start.x + 3 + (int)(detectionZone.width / TILE_SIZE);
  end.y = start.y + 4 + (int) (detectionZone.height / TILE_SIZE);

  // We don't want to check outside the level, so if the values are less than 0,
  // we should set them equal to 0
  if (start.x < 0)
    start.x = 0;
  if (start.y < 0)
    start.y = 0;
  if (end.x > m_levelSize.x)
    end.x = m_levelSize.x;
  if (end.y > m_levelSize.y)
    end.y = m_levelSize.y;

  // We also want to respawn the character if they fall out of the map
  // and subtract health
  // We want some padding on the sides of the level as well
  FloatRect levelRect(-4 * TILE_SIZE, -7 * TILE_SIZE,
     (m_levelSize.x + 8) * TILE_SIZE, (m_levelSize.y + 10) * TILE_SIZE);

  if (!levelRect.intersects(detectionZone)) {
    character.spawn(getStartingLocation(m_enteredFrom));
    character.incrementHealth(-1);
  }

  // These are the blocks that will stop a player
  char solidBlocks[] = {'b', 'c', 'd'};
  bool onGround = false;
  for (int y = start.y; y < end.y; y++) {
    for (int x = start.x; x < end.x; x++) {
      // Assign our block variable
      block.left = x * TILE_SIZE;
      block.top = y * TILE_SIZE;
      if ((block.left > detectionZone.left + TILE_SIZE / 4
        && block.left < detectionZone.left + detectionZone.width - TILE_SIZE / 4)
        && (block.top > detectionZone.top + TILE_SIZE / 4
          && block.top < detectionZone.top + detectionZone.top - TILE_SIZE / 4))
        continue;
      //cout << block.left << " " << (detectionZone.left + detectionZone.width) << endl;
      // Check for collision with feet
      if (contains(solidBlocks, m_levelArray[y][x])
      && character.getFeetHitbox().intersects(block)
      && character.getVelocity().y >= 0) {
        // Stop the player in the y direction only
        character.setVelocity(Vector2f(character.getVelocity().x, 0));
        // Also indicate that they are no longer in the air
        character.setInAir(false);
        character.setJumping(false);
        character.setFalling(false);
        character.setPosition(Vector2f(character.getCenter().x - detectionZone.width / 2, block.top - 2*block.height));
        onGround = true;
        // If we are the demon, we also want to subtract health
        if (character.canFly())
          character.takeDamage(1);
      }

      if (contains(solidBlocks, m_levelArray[y][x])
      && character.getHeadHitbox().intersects(block)
      && character.getVelocity().y <= 0) {
        // Stop the player in the y direction only
        character.setVelocity(Vector2f(character.getVelocity().x, 0));
        // Also indicate that they are no longer in the air
        //character.setInAir(false);
        character.setJumping(false);
        character.setFalling(true);
        if (character.canFly())
          character.takeDamage(1);
      }

      if (contains(solidBlocks, m_levelArray[y][x])
      && character.getLeftArmHitbox().intersects(block)
      && character.getVelocity().x < 0) {
        // Stop the player in the x direction only
        character.setVelocity(Vector2f(0, character.getVelocity().y));
        //cout << "Stopped left" << endl;
      }

      if (contains(solidBlocks, m_levelArray[y][x])
      && character.getRightArmHitbox().intersects(block)
      && character.getVelocity().x > 0) {
        // Stop the player in the x direction only
        character.setVelocity(Vector2f(0, character.getVelocity().y));
        //cout << "Stopped right" << endl;
      }

      /****** EXITS & ENTRANCES ******/
      // Next up, we want to be able to detect when the player moves from
      // level to level
      // We will use the first letter of the direction being moved to indicate
      // a doorway (eg. r move you right)

      if (m_levelArray[y][x] == 'r'
      && character.getHeadHitbox().intersects(block)) {
        character.setDirectionToMove(Direction::RIGHT);
      }

      if (m_levelArray[y][x] == 'l'
      && character.getHeadHitbox().intersects(block)) {
        character.setDirectionToMove(Direction::LEFT);
      }

      if (m_levelArray[y][x] == 'u'
      && character.getHeadHitbox().intersects(block)) {
        character.setDirectionToMove(Direction::UP);
      }

      if (m_levelArray[y][x] == 'd'
      && character.getHeadHitbox().intersects(block)) {
        character.setDirectionToMove(Direction::DOWN);
      }

      if (m_levelArray[y][x] == 'i'
      && character.getHeadHitbox().intersects(block)) {
        character.setDirectionToMove(Direction::IN);
      }

      if (m_levelArray[y][x] == 'o'
      && character.getHeadHitbox().intersects(block)) {
        character.setDirectionToMove(Direction::OUT);
      }


    }
  }
  // We do this after the for loop because otherwise a single non solid block
  // would mark the entire sprite as not being on the ground
  if (!onGround)
    character.setInAir(true);
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

Vector2i Level::getLevelSize() {
  return m_levelSize;
}

Vector2f Level::getStartingLocation(Direction dir) {
  m_enteredFrom = dir;
  return m_startingLocation[dir];
}

map<Direction, Vector2f> Level::getStartingLocations() {
  return m_startingLocation;
}

Sprite Level::getBackground() {
  return m_background;
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
  cout << "Tile Sheet: " << m_tileSheetPath << endl;
  cout << "Background: " << m_backgroundPath << endl;
  cout << endl;
}

bool contains(char* arr, char c) {
  for (int i = 0; i < sizeof(arr)/sizeof(*arr); i++) {
    if (arr[i] == c)
      return true;
  }
  return false;
}
