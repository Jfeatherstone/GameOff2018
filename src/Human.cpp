#include "headers/Human.h"

Human::Human() {
  m_health = m_maxHealth;
  m_name = "Human";
  m_healthTexturePath = "graphics/human_health.png";
  m_characterSprite.setTexture(TextureHolder::getTexture("graphics/human.png"));
  m_canFly = false;
}

bool Human::handleInput() {

}
