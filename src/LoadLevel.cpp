#include "headers/Level.h"
#include <fstream>
#include <list>
#include <cmath>

using namespace std;

float strToFloat(string s);

// Our definitions for the reading of the level file
const string START_X = "start_x";
const string START_Y = "start_y";
const string LOCATION = "location";
const string TILE_SHEET = "tile_sheet";
const string BACKGROUND = "background";

Level* Level::loadLevel(const string levelFilePath) {
  // We first want to open the file we're looking at
  fstream file(levelFilePath);
  string line;
  bool readingLevel = false;

  // Here we have the possible values that could be included in the file
  string startX;
  string startY;
  string location;
  string tileSheet;
  string background;

  // And the list for our level data
  list<string> levelData;

  while (getline(file, line)) {
    // We want to check that the first character is not a # (which denotes a comment)
    // If it is, we ignore it
    if (line.substr(0, 1) != "#") {
      // Next up, we want to see if the line denotes the start of our level map
      if (line == "<level>") {
        readingLevel = !readingLevel;
        continue;
      }

      // If we are currently reading the level, we add the values to a special list
      if (readingLevel) {
        // This will add our line at the end of the list, so they stay in order
        levelData.push_back(line);
      } else {
        // Otherwise, we just separate based on the = sign
        bool foundEquals = false;
        string value;
        string field;
        for (int i = 0; i < line.length(); i++) {
          if (line.substr(i, 1) == "=") {
            foundEquals = true;
            field = line.substr(0, i);
            value = line.substr(i + 1, line.length() - i);
            break;
          }
        }
        if (foundEquals) {
          // Assuming we found both our value and our field, we now want to
          // determine how to store the value according to the field

          if (field == START_X) {
            startX = value;
            continue;
          }
          if (field == START_Y) {
            startY = value;
            continue;
          }
          if (field == LOCATION) {
            location = value;
            continue;
          }
          if (field == TILE_SHEET) {
            tileSheet = value;
            continue;
          }
          if (field == BACKGROUND) {
            background = value;
            continue;
          }
        }
      }
    }
  }

  file.close();

  Vector2i levelSize;
  VertexArray vArray;
  // Now that we've read our entire file, we want to parse and interpret our data
  // First, we take a look at the level data
  if (levelData.size() > 0) {
    levelSize.y = levelData.size();

    for (string s: levelData) {
      levelSize.x = s.length();
    }

    // Now we create our int array, and populate it
    char arr[levelSize.x][levelSize.y];
    int x = 0;
    int y = 0;
    for (string s: levelData) {
      for (char c: s) {
        arr[x][y] = c;
        x++;
      }
      x = 0;
      y++;
    }

    // We now set up our vertex array variable
    vArray.setPrimitiveType(Quads);
    vArray.resize(levelSize.y * levelSize.x * VERTS_IN_QUAD);

    int currentVertex = 0;
    for (int x = 0; x < levelSize.x; x++) {
      for (int y = 0; y < levelSize.y; y++) {
        // Position our vertexes in a square to outline the tiles
        vArray[currentVertex + 0].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE);
        vArray[currentVertex + 1].position = Vector2f(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE);
        vArray[currentVertex + 2].position = Vector2f(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE + TILE_SIZE);
        vArray[currentVertex + 3].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE + TILE_SIZE);

        // Now we align these values with the spritesheet's dimensions to grab our tile
        // We subtract 97 because that is the character code for a, meaning our
        // code will just be the number the letter is in the alphabet
        int verticalOffset = (arr[y][x] - 97) * TILE_SIZE;

        vArray[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
        vArray[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
        vArray[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
        vArray[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

        currentVertex += VERTS_IN_QUAD;
      }
    }

    // Now that we have all of our data, we can make sure everything is in order
    // and return a new level
    Vector2f startingLocation;
    // Setup our starting location
    if (startX.length() > 0 && startY.length() > 0) {
      startingLocation.x = strToFloat(startX);
      startingLocation.y = strToFloat(startY);

      if (background.length() > 0 && tileSheet.length() > 0) {
        // Once our starting location is set, we can setup our textures
        Texture backgroundTexture = TextureHolder::getTexture(background);

        return new Level(levelSize, startingLocation, backgroundTexture, tileSheet, vArray, location, arr);
      }
    }
  }
  return new Level();
}

/*
This is just for converting values read in from the text file
*/
float strToFloat(string s) {
  float value = 0;
  int multiplier = s.length() - 1;
  for (int i = 0; i < s.length(); i++) {
    value += atof(s.substr(i, 1).c_str()) * (pow(10, multiplier - i));
  }
  return value;
}
