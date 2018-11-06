#include "headers/NLLinkedList.h"

using namespace std;

template <class T>
NLLinkedList<T>::NLLinkedList(T originNode) {
  origin = originNode;
  currentNode = origin;

  // We now place the origin node at the 0 0 0 position in our map
  currentKey = "0 0";
  llMap[currentKey] = origin;
}

template<class T>
T NLLinkedList<T>::get(Direction direction) {

  // Two of these will stay at zero, but the other will be either 1 or -1
  int dx = 0;
  int dy = 0;

  switch (direction) {
    case Direction::LEFT:

      break;
    case Direction::RIGHT:

      break;
    case Direction::UP:

      break;
    case Direction::DOWN:

      break;
  }

}

template<class T>
int* NLLinkedList<T>::separateKey() {
  // We want to look for the spaces within our string and parse the substrings
  // into their respective ints
  int* arr = new int[2];
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
