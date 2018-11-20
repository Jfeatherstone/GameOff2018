#pragma once
#include "PlayableCharacter.h"

class Demon: public PlayableCharacter {
public:
  Demon();
  bool handleInput(float elapsedTime);
};
