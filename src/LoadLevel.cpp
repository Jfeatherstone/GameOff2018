#include "headers/Level.h"
#include <fstream>
#include <list>
#include <cmath>
#include <iostream>

using namespace std;

// These methods will be used to read in the starting positions
float strToFloat(string s);
string removeSpaces(string& str);
string* splitByString(string str, string split);
Direction valueOfDirection(string value);

// Our definitions for the reading of the level file
const string START_LOCATION = "start_location";
const string LOCATION = "location";
const string TILE_SHEET = "tile_sheet";
const string BACKGROUND = "background";

Level Level::loadLevel(const string levelFilePath) {
  // We first want to open the file we're looking at
  fstream file(levelFilePath);
  string line;
  bool readingLevel = false;

  // Here we have the possible values that could be included in the file
  map<Direction, Vector2f> startLocations;
  string location;
  string tileSheet;
  string background;

  // And the list for our level data
  list<string> levelData;
  try {
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
          //cout << line << endl;
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

            if (field == START_LOCATION) {
              // The value will be of the form "Direction, x, y", so we want to
              // split it by the comma
              // First though, we remove the spaces to avoid any conflicts
              removeSpaces(value);
              // Next we split the value into it's three parts
              string* arr = splitByString(value, ",");
              // Now we create our vector and add it to the map
              Vector2f vector;
              vector.x = strToFloat(arr[1]);
              vector.y = strToFloat(arr[2]);

              if (valueOfDirection(arr[0]) == Direction::NONE) {
                string error = "Invalid direction provided for start location: \"" + arr[0] + "\"!";
                throw error;
              }

              startLocations[valueOfDirection(arr[0])] = vector;

              // Clean up our memory
              delete[] arr;
              continue;
            } else
            if (field == LOCATION) {
              location = value;
              continue;
            } else
            if (field == TILE_SHEET) {
              tileSheet = value;
              continue;
            } else
            if (field == BACKGROUND) {
              background = value;
              continue;
            } else {
              string error = "Invalid level parameter: /""" + field + "/""!";
              throw error;
            }
          }
        }
      }
    }
  } catch (string exception) {
    cout << "Exception thrown while reading file: \n"
          << levelFilePath << "\nDetails: " << exception << endl;
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
    // TODO: This may create a memory leak because of the array initialization
    char** arr = new char*[levelSize.y];
    for (int i = 0; i < levelSize.y; i++)
      arr[i] = new char[levelSize.x];

    int x = 0;
    int y = 0;
    for (string s: levelData) {
      for (char c: s) {
        arr[y][x] = c;
        //cout << (int) arr[y][x];
        x++;
      }
      x = 0;
      y++;
      //cout << endl;
    }

    // We now set up our vertex array variable
    vArray.setPrimitiveType(Quads);
    vArray.resize(levelSize.y * levelSize.x * VERTS_IN_QUAD);

    int currentVertex = 0;
    // Since we already defined x and y, we don't need to specify a type again
    for (y = 0; y < levelSize.y; y++) {
      for (x = 0; x < levelSize.x; x++) {
        // Position our vertexes in a square to outline the tiles
        vArray[currentVertex + 0].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE);
        vArray[currentVertex + 1].position = Vector2f(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE);
        vArray[currentVertex + 2].position = Vector2f(x * TILE_SIZE + TILE_SIZE, y * TILE_SIZE + TILE_SIZE);
        vArray[currentVertex + 3].position = Vector2f(x * TILE_SIZE, y * TILE_SIZE + TILE_SIZE);

        // Now we align these values with the spritesheet's dimensions to grab our tile
        // We subtract 97 because that is the character code for a, meaning our
        // code will just be the number the letter is in the alphabet
        //cout << arr[y][x];
        int verticalOffset = (arr[y][x] - 97) * TILE_SIZE;

        vArray[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
        vArray[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
        vArray[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
        vArray[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

        currentVertex += VERTS_IN_QUAD;
      }
      //cout << endl;
    }

    // Now that we have all of our data, we can make sure everything is in order
    // and return a new level

    if (background.length() > 0 && tileSheet.length() > 0) {
      // Once our starting location is set, we can setup our textures
      Texture backgroundTexture = TextureHolder::getTexture(background);

      return *(new Level(levelSize, startLocations, backgroundTexture, tileSheet, vArray, location, arr));
    }
  } else {
    cout << "Invalid level data in file \"" << levelFilePath << "\"!";
  }
  return Level();
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

string removeSpaces(string& str) {
  string newString;
  for (int i = 0; i < str.length(); i++) {
    if (str.substr(i, 1) != " ")
      newString += str.substr(i, 1);
  }
  str = newString;
  return newString;
}

string* splitByString(string str, string split) {
  string* arr = new string[3];
  int prevIndex = 0;
  int arrIndex = 0;
  for (int i = 0; i < str.length(); i++) {
    if (str.substr(i, split.length()) == split) {
      arr[arrIndex++] = str.substr(prevIndex, i - prevIndex);
      prevIndex = i + 1;
    }
  }
  arr[arrIndex] = str.substr(prevIndex, str.length() - prevIndex);
  return arr;
}

Direction valueOfDirection(string value) {
  // This makes the string lowercase
  transform(value.begin(), value.end(), value.begin(), ::tolower);

  if (value == "up")
    return Direction::UP;
  if (value == "down")
    return Direction::DOWN;
  if (value == "left")
    return Direction::LEFT;
  if (value == "right")
    return Direction::RIGHT;
  if (value == "in")
    return Direction::IN;
  if (value == "out")
    return Direction::OUT;

  return Direction::NONE;
}
