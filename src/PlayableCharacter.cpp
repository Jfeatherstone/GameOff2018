#include "headers/PlayableCharacter.h"

void PlayableCharacter::spawn(Vector2f position) {
  // First, we set our characters's location
  m_position.x = position.x;
  m_position.y = position.y;
  m_characterSprite.setPosition(m_position);
  //cout << m_position.x << " " << m_position.y << endl;
}

void PlayableCharacter::update(float elapsedTime) {
  // Move our character
  m_position.x += m_velocity * elapsedTime;
  //cout << m_position.x << " " << m_position.y << endl;
  m_characterSprite.setPosition(m_position);
}

string PlayableCharacter::getHealthTexturePath() {
  return m_healthTexturePath;
}

int PlayableCharacter::getHealth() {
  return m_health;
}

Sprite PlayableCharacter::getSprite() {
  return m_characterSprite;
}
