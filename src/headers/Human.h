#pragma once
#include "PlayableCharacter.h"

class Human: public PlayableCharacter {
public:
  Human();
  bool handleInput();
};
