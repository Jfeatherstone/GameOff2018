#include "headers/Human.h"

Human::Human() {
  m_health = m_maxHealth;
  m_name = "Human";
  m_healthTexturePath = "graphics/human_health.png";
  m_characterSprite.setTexture(TextureHolder::getTexture("graphics/human.png"));
  m_canFly = false;
  m_startingVelocity = 100;
}

bool Human::handleInput(float elapsedTime) {
  // Handling right movement
  if (Keyboard::isKeyPressed(Keyboard::D)) {
    cout << m_velocity << endl;
    if (m_velocity > 0) {
      m_velocity += m_acceleration * m_startingVelocity * elapsedTime;
      if (m_velocity > m_accelerationCap * m_startingVelocity)
        m_velocity = m_accelerationCap * m_startingVelocity;

    } else {
      // We'll accelerate a 3 times the speed if we are turning around
      m_velocity += 5 * m_acceleration * m_startingVelocity * elapsedTime;
    }
  }

  // Handling left movement
  if (Keyboard::isKeyPressed(Keyboard::A)) {
    cout << m_velocity << endl;
    if (m_velocity < 0) {
      m_velocity -= m_acceleration * m_startingVelocity * elapsedTime;
      if (m_velocity < - m_accelerationCap * m_startingVelocity)
        m_velocity = - m_accelerationCap * m_startingVelocity;

    } else {
      m_velocity -= 5 * m_acceleration * m_startingVelocity * elapsedTime;
    }
  }

  // Reset our velocity if we aren't pressing anything
  if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
    m_velocity = 0;
}
