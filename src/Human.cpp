#include "headers/Human.h"

Human::Human() {
  m_health = m_maxHealth;
  m_name = "Human";
  m_healthTexturePath = "graphics/human_health.png";
  m_characterSprite.setTexture(TextureHolder::getTexture("graphics/human.png"));
  m_canFly = false;
  m_startingVelocity = 250;
  m_terminalVelocity = 1200;
}

bool Human::handleInput(float elapsedTime) {
  bool jumped = false;
  //cout << m_startingVelocity << endl;
  // Handling right movement
  if (Keyboard::isKeyPressed(Keyboard::D)) {
    //cout << m_velocity << endl;
    if (m_velocity.x > 0 && m_velocity.x <= m_accelerationCap * m_startingVelocity) {
        m_velocity.x += m_acceleration * m_startingVelocity * elapsedTime;
    } else if (m_velocity.x > m_accelerationCap * m_startingVelocity)
        m_velocity.x -= .15 * elapsedTime * m_acceleration * m_startingVelocity;
    else {
        // We'll accelerate a 5 times the speed if we are turning around
        m_velocity.x += 5 * m_acceleration * m_startingVelocity * elapsedTime;
      }
  }

  // Handling left movement
  if (Keyboard::isKeyPressed(Keyboard::A)) {
    //cout << m_velocity << endl;
    if (m_velocity.x < 0 && m_velocity.x >= - m_accelerationCap * m_startingVelocity) {
      m_velocity.x -= m_acceleration * m_startingVelocity * elapsedTime;
    } else if (m_velocity.x < - m_accelerationCap * m_startingVelocity)
      m_velocity.x += .15 * elapsedTime * m_acceleration * m_startingVelocity;
    else {
      m_velocity.x -= 5 * m_acceleration * m_startingVelocity * elapsedTime;
    }
  }

  // Reset our velocity if we aren't pressing anything
  if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
    m_velocity.x = 0;

  // Next, we want to handle jumping
  if (Keyboard::isKeyPressed(Keyboard::W) && !m_inAir) {
    m_inAir = true;
    jumped = true;
  }

  return jumped;
}
