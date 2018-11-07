#include "headers/NLLinkedList.h"
#include <sstream>

using namespace std;

template <class T>
NLLinkedList<T>::NLLinkedList(T originNode) {
  origin = originNode;
  currentNode = origin;

  // We now place the origin node at the 0 0 0 position in our map
  currentKey = "0 0 0";
  llMap[currentKey] = origin;
}

template<class T>
T NLLinkedList<T>::get(Direction direction) {

  // Two of these will stay at zero, but the other will be either 1 or -1
  int dx = 0;
  int dy = 0;
  int dz = 0;

  Vector2i key = separateKey();

  switch (direction) {
    case Direction::LEFT:
      dx = -1;
      break;
    case Direction::RIGHT:
      dx = 1;
      break;
    case Direction::UP:
      dy = 1;
      break;
    case Direction::DOWN:
      dy = -1;
      break;
  }

  // We can now create our tenative new key and see if there is a value
  string tenativeKey = formKey(key.x + dx, key.y + dy);

  // Now we plug this into our map to find out if there is a proper value there
  if (llMap[tenativeKey] != nullptr) {
    currentKey = tenativeKey;
    currentNode = llMap[currentKey];
    return currentNode;
  } else {
    return nullptr;
  }
}

/*
This method is rather simple, though it makes sure that all of the variables
are put together correctly.
*/
template<class T>
string NLLinkedList<T>::formKey(int x, int y, int z) {
  stringstream s;
  s << x << " " << y << " " << z;
  return s.str();
}

/*
This method takes our string of the form "x y z" and separates the values and
parses them all into integers.
*/
template<class T>
int* NLLinkedList<T>::separateKey() {
  // We want to look for the spaces within our string and parse the substrings
  // into their respective ints
  int* arr = new int[3];
  int prevIndex = 0;
  int arrIndex = 0;
  for (int i = 0; i < currentKey.length(); i++) {
    if (currentKey.substr(i, 1) == " ") {
      arr[arrIndex++] = stoi(currentKey.substr(prevIndex, i - prevIndex));
      prevIndex = i + 1;
    }
  }
  arr[arrIndex] = stoi(currentKey.substr(prevIndex, currentKey.length() - prevIndex));

  return arr;
}
