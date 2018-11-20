#include "headers/PlayableCharacter.h"

string PlayableCharacter::getHealthTexturePath() {
  return m_healthTexturePath;
}

int PlayableCharacter::getHealth() {
  return m_health;
}

Sprite PlayableCharacter::getSprite() {
  return m_characterSprite;
}
