#pragma once
#include <map>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
/*
Since our non-linear linked list will have values which are related to each
other based on diretions, not just binary values

The none state should never be used within this class, but will be used in the
game loop, to determine when we need a new level

We also want to define an array of strings to be able to print out the enums
*/
enum Direction {NONE = 0, LEFT, RIGHT, UP, DOWN, IN, OUT};
static const string DIRECTION_NAMES[] = {"None", "Left", "Right", "Up", "Down", "In", "Out"};
/*
The basis of our class will be a map<string, T>, where the string will be an
indicator of the node's relationship between surrounding nodes
*/
template <class T>
class NLLinkedList {
private:
  // The origin data point, at the very "center" of the list
  T origin;

  // Our list will keep track of the current location of our "pointer"
  T currentNode;

  // Our map, which will be the hidden foundation of our linked list
  map<string, T> llMap;

  // We also need to keep track to the current string key
  string currentKey;

  // This will return the x, y, and z integers for the key
  int* separateKey();

  // This will recompile the key with new int values, after they have
  // been modified
  string formKey(int x, int y, int z);

  // Our original key, the value "0 0 0"
  const string ORIGIN_KEY = "0 0 0";

public:
  // Our constructor which will be provided the origin node
  NLLinkedList(T originNode); // Done
  NLLinkedList();

  // Getting methods
  bool gotoNode(T node); // Done
  T getOrigin(); // Done
  T get(Direction direction); // Done
  T getCurrent(); // Done

  // Adding methods
  void add(T newNode, Direction direction); // Done
  void setOrigin(T newOrigin); // Done
  bool replace(T oldNode, T newNode); // Done

  // Management methods
  void reset(); // Done
  void reset(T newOrigin); // Done

  // This is so we can print out enums
};
