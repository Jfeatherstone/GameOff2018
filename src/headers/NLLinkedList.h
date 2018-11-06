#pragma once
#include <map>
using namespace std;

/*
Since our non-linear linked list will have values which are related to each
other based on diretions, not just binary values
*/
enum class Direction {LEFT, RIGHT, UP, DOWN};

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

  // This will return the x and y integers for the key
  int* separateKey();
  // This will recompile the key with new int values, after they have
  // been modified
  string formKey(int x, int y);

public:
  // Our constructor which will be provided the origin node
  NLLinkedList(T originNode);
  T gotoNode(T node);
  T gotoOrigin();
  T get(Direction direction);
  T getCurrent();
  void add(T newNode, Direction direction);
  void setOrigin(T newOrigin);
};
