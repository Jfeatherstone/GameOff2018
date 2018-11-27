#include "headers/Demon.h"

Demon::Demon() {
  m_health = m_maxHealth;
  m_name = "Demon";
  m_healthTexturePath = "graphics/demon_health.png";
  m_characterSprite.setTexture(TextureHolder::getTexture("graphics/demon.png"));
  m_canFly = true;
  m_startingVelocity = 350;
  m_terminalVelocity = 800;
  m_jumpDuration = .55f;
}

bool Demon::handleInput(float elapsedTime) {
  bool jumped = false;
  //cout << m_startingVelocity << endl;
  // Handling right movement
  if (Keyboard::isKeyPressed(Keyboard::D)) {
    //cout << m_velocity << endl;
  if (m_velocity.x > 0 && m_velocity.x <= m_accelerationCap * m_startingVelocity) {
      m_velocity.x += m_acceleration * m_startingVelocity * elapsedTime;
  } else if (m_velocity.x > m_accelerationCap * m_startingVelocity)
      m_velocity.x -= .15 * m_acceleration * m_startingVelocity * elapsedTime;
  else {
      // We'll accelerate a 3 times the speed if we are turning around
      m_velocity.x += 5 * m_acceleration * m_startingVelocity * elapsedTime;
    }
  }

  // Handling left movement
  if (Keyboard::isKeyPressed(Keyboard::A)) {
    //cout << m_velocity << endl;
    if (m_velocity.x < 0 && m_velocity.x >= - m_accelerationCap * m_startingVelocity) {
      m_velocity.x -= m_acceleration * m_startingVelocity * elapsedTime;
    } else if (m_velocity.x < - m_accelerationCap * m_startingVelocity)
      m_velocity.x += .15 * m_acceleration * m_startingVelocity * elapsedTime;
    else {
      m_velocity.x -= 5 * m_acceleration * m_startingVelocity * elapsedTime;
    }
  }

  // Reset our velocity if we aren't pressing anything
  if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D))
    m_velocity.x = 0;

  // "Jumping"
  // Since this is actually flying, the player doesn't need to be on the ground
  if (Keyboard::isKeyPressed(Keyboard::W) && !m_jumping) {
    m_inAir = true;
    jumped = true;
    m_jumping = true;
    m_currentJumpTime = 0;
    m_velocity.y = - m_terminalVelocity * .75;
  }

  return jumped;
}
