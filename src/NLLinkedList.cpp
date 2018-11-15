#include "headers/NLLinkedList.h"
#include "headers/Level.h"
#include <sstream>
#include <iostream>

using namespace std;

/***** PUBLIC METHODS *****/


/***** INITIALIZING METHODS *****/

/*
Our public constructor
This will be used to initialize our linked list, and will set the current node
to be the origin.
*/
template <class T>
NLLinkedList<T>::NLLinkedList(T originNode) {
  origin = originNode;
  currentNode = origin;

  // We now place the origin node at the 0 0 0 position in our map
  currentKey = ORIGIN_KEY;
  llMap[currentKey] = origin;
}

template <class T>
NLLinkedList<T>::NLLinkedList() {
  T originNode = T();
  origin = originNode;
  currentNode = origin;

  // We now place the origin node at the 0 0 0 position in our map
  currentKey = ORIGIN_KEY;
  llMap[currentKey] = origin;

  //cout << "No arg constructor" << endl;
}
/*
Similar to the previous constructor, this method will set the origin node
equal to a new value, but leave the rest of the values the same. This will also
assign the current working node to be the origin
*/
template<class T>
void NLLinkedList<T>::setOrigin(T node) {
  origin = node;
  currentNode = origin;
  currentKey = ORIGIN_KEY;
  llMap[currentKey] = origin;
}

/*
This method will reset our linked list, clearing all values for the underlying
map. This will also set the current node to be the origin

NOTE: Calling this function and then attempting to get any value in ANY direction
will always result in a runtime error. DON'T DO IT. If you would like to reset
the entire list AND provide a new origin, use the overloaded version of this
method below
*/
template<class T>
void NLLinkedList<T>::reset() {
  // Remove all entries from the map
  llMap.clear();
  // Clean up our keys, those you'll still error up if you try and access these
  currentKey = ORIGIN_KEY;
  currentNode = T();
}

/*
The overloaded version of the above method, which will not only clear the entire
list, but will also  set a new origin node
*/
template<class T>
void NLLinkedList<T>::reset(T newOrigin) {
    // Clear the map
    llMap.clear();
    currentKey = ORIGIN_KEY;
    // Add the new node to the map at the origin
    llMap[currentKey] = newOrigin;
    currentNode = newOrigin;
}

/***** END INITIALIZING METHODS *****/


/***** VALUE GETTING METHODS *****/

/*
This method will return the node to the left/right/up/down/in/out of the current
node. This will mostly be used when traversing through the list, in our case for
moving between levels
*/
template<class T>
T NLLinkedList<T>::get(Direction direction) {

  // Two of these will stay at zero, but the other will be either 1 or -1
  int dx = 0;
  int dy = 0;
  int dz = 0;

  int* key = separateKey();

  // Depending on which direction we're trying to go, we should modify the
  // appropriate variable, and leave the others at 0
  // This makes sure that we only ever move 1 node in one direction at any time

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
    case Direction::IN:
      dz = -1;
      break;
    case Direction::OUT:
      dz = 1;
      break;
    case Direction::NONE:
      // Do nothing here
      break;
  }

  // We can now create our tenative new key and see if there is a value
  string tenativeKey = formKey(key[0] + dx, key[1] + dy, key[2] + dz);

  // Don't want to have excess memory being used
  delete[] key;

  // Now we plug this into our map to find out if there is a proper value there
  // This may seem like the stupidest if statement ever written, but there is
  // an actual reason as to why I didn't being a decent human being and just use
  // the != operator. Since we will mainly be using lists with the Level class,
  // which having been defined by us, does not automatically have == and !=
  // defined, by using only the == operator, we avoid having to define != operator
  // in the first place. :)
  if (!(llMap[tenativeKey] == T())) {
    currentKey = tenativeKey;
    currentNode = llMap[currentKey];
    return currentNode;
  } else {
    return T();
  }
}

/*
This one's pretty simple, as it just returns the current node
*/
template<class T>
T NLLinkedList<T>::getCurrent() {
  return currentNode;
}

/*
This one is similar to the last one, except we also have to adjust the current
key
*/
template<class T>
T NLLinkedList<T>::getOrigin() {
  currentKey = ORIGIN_KEY;
  return origin;
}

/*
This is gonna be the big boy method, because we will have to search through each
entry in the map to try and find the correct node. This won't actually be
as terrible as it could be, as we can use an iterator for our map and compare
each value.

We return the boolean of whether or not we have found the node given
*/
template<class T>
bool NLLinkedList<T>::gotoNode(T node) {
  // We first want to find the node provided in the map
  // We want to keep track of whether we found the node or not
  bool foundNode = false;

  // Iterate through the map using an auto type to simplify stuff
  for (auto element: llMap) {
    // Compare the value in each entry to the given node
    if (element.second == node) {
      // Assign our new key, currentNode, and our bool
      currentKey = element.first;
      currentNode = element.second;
      foundNode = true;
      // We now have no reason to iterate through the rest of the map
      return foundNode;
    }
  }

  // If the code ever gets here, foundNode should be false
  return foundNode;
}

/*
This will be rather similar to the previous method, but will instead replace
the node with a new one.

It's possible that we can corrupt some stuff with concurrent modication here
but you win some you lose some...

Most of the code is actually copied, so that's why they're almost identical
*/
template<class T>
bool NLLinkedList<T>::replace(T oldNode, T newNode) {

  // We want to keep track of whether we found the node or not
  bool foundNode = false;

  // Iterate through the map using an auto type to simplify stuff
  for (auto element: llMap) {
    // Compare the value in each entry to the given node
    if (element.second == oldNode) {
      // Assign our new key, currentNode, map value, and our bool
      // This hopefully won't hit us with a concurrent modication error for
      // changing the map while iterating through it
      // If something went wrong, its probably here TODO
      currentKey = element.first;
      llMap[currentKey] = newNode;
      currentNode = newNode;
      foundNode = true;
      // We now have no reason to iterate through the rest of the map
      return foundNode;
    }
  }

  // If the code ever gets here, foundNode should be false
  return foundNode;

}

/*
Most of the code for this one is taken from the get(Direction direction) method
*/
template<class T>
void NLLinkedList<T>::add(T node, Direction direction) {
    // Two of these will stay at zero, but the other will be either 1 or -1
    int dx = 0;
    int dy = 0;
    int dz = 0;

    int* key = separateKey();

    // Depending on which direction we're trying to go, we should modify the
    // appropriate variable, and leave the others at 0
    // This makes sure that we only ever move 1 node in one direction at any time

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
      case Direction::IN:
        dz = -1;
        break;
      case Direction::OUT:
        dz = 1;
        break;
      case Direction::NONE:
        // Do nothing here
        break;
    }

    currentKey = formKey(key[0] + dx, key[1] + dy, key[2] + dz);
    llMap[currentKey] = node;
    currentNode = node;
    delete[] key;

}
/***** END VALUE GETTING METHODS *****/



/***** PRIVATE METHODS *****/
/*
This method is rather simple, though it makes sure that all of the variables
are put together correctly every time.
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

/*
Since I defined all of this code not in the header class, we get errors if we
just straight try to create a list of any type. As of now, the way I know
how to fix this is by defining template classes below for the types we want
In this case, we only need this class for levels, so we define that below
*/

template class NLLinkedList<Level>;
template class NLLinkedList<string>;
