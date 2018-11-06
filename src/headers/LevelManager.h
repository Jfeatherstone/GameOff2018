#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"

using namespace sf;
using namespace std;
/*
Class Synopsis:
This class will be the cornerstone of mapping individual levels together such
that the player can easily travel between them with (hopefully) every
short loading times. This includes a method that will initialize all levels
from their text files and create a map between them, all at the creation of
the class instance.

NOTE: for more information on the structure of individual levels, see Level.h

For now, we need to figure out how to store the levels in an accessible way
As of now, the options (that I'm considering) are:
>> map<string, Level>
  We could use a map with all of the levels stored as values, while the key is
  some string which represents the levels "location" relative to others. This would
  be something like "0 0 0" where "0 0 1" would be to the right and "0 0 -1" would
  be to the left or something
>> linkedlist
  We could create a type of linkedlist that allows for the next and previous levels
  to be directly intertwined with the level itself. The downside to this is that it
  would likely cause for the levels to be linear, and wouldn't allow for branching
>> non-linear linked list
  This would be similar to the previous option, but would be a linked list where
  instead of just have next() and previous() references for each data item, we
  would have left(), right(), up(), down(). This would be a kind of 3d linked
  list, though this may be much harder to code and/or a slower solution.
*/
class LevelManager {
private:

  // To read in all of the levels
  // This will use the std::filesystem to find all of the files within
  // the directory and read in their data
  // Since we don't quite know how to store levels, this will stay commented out
  // for now at least
  //parseLevels(const string levelFolderPath);

  // Just for extra abstraction, we will make a method that reads individual levels
  Level parseLevel(const string filePath);
public:
  LevelManager();
};
