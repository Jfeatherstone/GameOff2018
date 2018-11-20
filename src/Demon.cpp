#include "headers/Demon.h"

Demon::Demon() {
  m_health = m_maxHealth;
  m_name = "Demon";
  m_healthTexturePath = "graphics/demon_health.png";
  m_characterSprite.setTexture(TextureHolder::getTexture("graphics/demon.png"));
  m_canFly = true;
}

bool Demon::handleInput() {

  return false;
}
