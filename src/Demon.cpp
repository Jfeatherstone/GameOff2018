#include "headers/Demon.h"

Demon::Demon() {
  m_health = m_maxHealth;
  m_name = "Demon";
  m_healthTexturePath = "graphics/demon_health.png";
  m_characterSprite.setTexture(TextureHolder::getTexture("graphics/demon.png"));
  m_canFly = true;
  m_startingVelocity = 350;
}

bool Demon::handleInput(float elapsedTime) {
  //cout << m_startingVelocity << endl;
  // Handling right movement
  if (Keyboard::isKeyPressed(Keyboard::D)) {
    //cout << m_velocity << endl;
    if (m_velocity > 0) {
      m_velocity += m_acceleration * m_startingVelocity * elapsedTime;
      if (m_velocity > m_accelerationCap * m_startingVelocity)
        m_velocity -= m_accelerationCap * m_startingVelocity * elapsedTime;

    } else {
      // We'll accelerate a 5 times the speed if we are turning around
      m_velocity += 5 * m_acceleration * m_startingVelocity * elapsedTime;
    }
  }

  // Handling left movement
  if (Keyboard::isKeyPressed(Keyboard::A)) {
    //cout << m_velocity << endl;
    if (m_velocity < 0) {
      m_velocity -= m_acceleration * m_startingVelocity * elapsedTime;
      if (m_velocity < - m_accelerationCap * m_startingVelocity)
        m_velocity += m_accelerationCap * m_startingVelocity * elapsedTime;

    } else {
      m_velocity -= 5 * m_acceleration * m_startingVelocity * elapsedTime;
    }
  }

  // Reset our velocity if we aren't pressing anything
  if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
    m_velocity = 0;
}
