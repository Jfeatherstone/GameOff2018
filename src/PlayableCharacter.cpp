#include "headers/PlayableCharacter.h"

void PlayableCharacter::spawn(Vector2f position) {
  // First, we set our characters's location
  m_position.x = position.x;
  m_position.y = position.y;
  m_characterSprite.setPosition(m_position);
  m_characterSprite.setOrigin(getPosition().width / 2, getPosition().height / 2);
  //cout << m_position.x << " " << m_position.y << endl;
  // So the player doesn't immediately die
  m_timeSinceDamage = .5;
}

void PlayableCharacter::update(float elapsedTime) {

  //cout << m_falling << " " << m_jumping << " " << m_inAir << endl;
  // Update our damage cooldown
  m_timeSinceDamage += elapsedTime;

  // Apply gravity acceleration
  if (m_inAir)
    m_velocity.y += - (m_velocity.y - m_terminalVelocity) * elapsedTime * m_gravityAcceleration;

  // Keep track of our jump time and when its over
  if (m_jumping) {
    m_currentJumpTime += elapsedTime;
    //cout << m_currentJumpTime << endl;
    if (m_currentJumpTime >= m_jumpDuration) {
      m_jumping = false;
      m_velocity.y = 0;
    }
  }

  // Move our character
  m_position.x += m_velocity.x * elapsedTime;
  m_position.y += m_velocity.y * elapsedTime;
  //cout << m_velocity.x << " " << m_velocity.y << endl;
  m_characterSprite.setPosition(m_position);

  FloatRect r = getPosition();

  // If we are the demon, we want to align our wings as well
  updateWings(elapsedTime);
  m_wingIndex++;
  if (m_wingIndex >= m_wingSpeed * 14)
    m_wingIndex = 0;
  // We now want to update our hitboxes
  // The extra numbers are to provide a slight padding on the sprite
  //if (!m_canFly) {
    m_feetHitbox.left = r.left + 7;
    m_feetHitbox.width = r.width - 14;
    m_feetHitbox.top = r.top + r.height - 4;
    m_feetHitbox.height = 4;

    m_headHitbox.left = r.left + 6;
    m_headHitbox.width = r.width - 12;
    m_headHitbox.top = r.top + 1;
    m_headHitbox.height = 20;

    m_leftArmHitbox.left = r.left;
    m_leftArmHitbox.width = 1;
    m_leftArmHitbox.top = r.top + 28;
    m_leftArmHitbox.height = 36;

    m_rightArmHitbox.left = r.left + r.width - 1;
    m_rightArmHitbox.width = 1;
    m_rightArmHitbox.top = r.top + 28;
    m_rightArmHitbox.height = 36;
  /*} else {
    // For the demon, we will load in a sprite of just the wing to do some calculations

    Texture wingTexture = TextureHolder::getTexture("graphics/demon_wing.png");
    Vector2u wing = wingTexture.getSize();

    int wingOverlap = 3;

    m_feetHitbox.left = r.left + 7 + wing.x - wingOverlap;
    m_feetHitbox.width = r.width - 14 - 2 * wing.x + 2 * wingOverlap;
    m_feetHitbox.top = r.top + r.height - 4;
    m_feetHitbox.height = 4;

    m_headHitbox.left = r.left + 6 + wing.x - wingOverlap;
    m_headHitbox.width = r.width - 12 - 2 * wing.x + 2 * wingOverlap;
    m_headHitbox.top = r.top + 1;
    m_headHitbox.height = 20;

    m_leftArmHitbox.left = r.left + wing.x - wingOverlap;
    m_leftArmHitbox.width = 1;
    m_leftArmHitbox.top = r.top + 28;
    m_leftArmHitbox.height = 36;

    m_rightArmHitbox.left = r.left + r.width - 1 - wing.x + wingOverlap;
    m_rightArmHitbox.width = 1;
    m_rightArmHitbox.top = r.top + 28;
    m_rightArmHitbox.height = 36;

  }*/
}

void PlayableCharacter::updateWings(float elapsedTime) {
  FloatRect r = getPosition();
  if (m_canFly) {
    // Go to the next frame if we are flying
    if (m_inAir) {
      if (m_wingIndex % m_wingSpeed == 0) {
        m_rightWing.setTextureRect(IntRect(0, m_wingIndex / m_wingSpeed * wingSize.y, wingSize.x, wingSize.y));
        m_leftWing.setTextureRect(IntRect(0, m_wingIndex / m_wingSpeed * wingSize.y, wingSize.x, wingSize.y));
      }
      //m_wingIndex++;
    }
    // And then attach the wings at the right spot
    m_rightWing.setPosition(r.left + r.width - 5, r.top - 7);
    m_leftWing.setPosition(r.left + 5 - 2 * r.width, r.top - 7);
  }
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

Sprite PlayableCharacter::getLeftWing() {
  return m_leftWing;
}

Sprite PlayableCharacter::getRightWing() {
  return m_rightWing;
}

void PlayableCharacter::setPosition(Vector2f position) {
  m_position.x = position.x;
  m_position.y = position.y;
  m_characterSprite.setPosition(m_position);
}

void PlayableCharacter::setVelocity(Vector2f velocity) {
  m_velocity.x = velocity.x;
  m_velocity.y = velocity.y;
}

int PlayableCharacter::getWingSpeed() {
  return m_wingSpeed;
}

Vector2f PlayableCharacter::getVelocity() {
  return m_velocity;
}

FloatRect PlayableCharacter::getPosition() {
  return m_characterSprite.getGlobalBounds();
}

FloatRect PlayableCharacter::getFeetHitbox() {
  return m_feetHitbox;
}

FloatRect PlayableCharacter::getHeadHitbox() {
  return m_headHitbox;
}

FloatRect PlayableCharacter::getLeftArmHitbox() {
  return m_leftArmHitbox;
}

FloatRect PlayableCharacter::getRightArmHitbox() {
  return m_rightArmHitbox;
}

void PlayableCharacter::setDirectionToMove(Direction dir) {
  m_directionToMove = dir;
}

Direction PlayableCharacter::getDirectionToMove() {
  return m_directionToMove;
}

void PlayableCharacter::setInAir(bool inAir) {
  m_inAir = inAir;
}

void PlayableCharacter::setJumping(bool jumping) {
  m_jumping = jumping;
}

void PlayableCharacter::setFalling(bool falling) {
  m_falling = falling;
}

bool PlayableCharacter::canFly() {
  return m_canFly;
}

Vector2f PlayableCharacter::getCenter() {
  return Vector2f(m_position.x, m_position.y);
}

void PlayableCharacter::setHealth(int health) {
  m_health = health;
}

void PlayableCharacter::setWingIndex(int index) {
  m_wingIndex = index;
}

int PlayableCharacter::getWingIndex() {
  return m_wingIndex;
}


void PlayableCharacter::takeDamage(int amount) {
  if (m_timeSinceDamage > m_damageCooldown) {
    m_health -= amount;
    m_timeSinceDamage = 0;
  }
}

void PlayableCharacter::incrementHealth(int increment) {
  m_health += increment;
}

void PlayableCharacter::setScore(int score) {
  m_score = score;
}

void PlayableCharacter::incrementScore(int increment) {
  m_score += increment;
}

int PlayableCharacter::getScore() {
  return m_score;
}

RectangleShape PlayableCharacter::feetHitboxDrawable() {
  RectangleShape feet;
  feet.setPosition(m_feetHitbox.left, m_feetHitbox.top);
  feet.setSize(Vector2f(m_feetHitbox.width, m_feetHitbox.height));
  feet.setFillColor(Color::Magenta);
  return feet;
}

RectangleShape PlayableCharacter::headHitboxDrawable() {
  RectangleShape head;
  head.setPosition(m_headHitbox.left, m_headHitbox.top);
  head.setSize(Vector2f(m_headHitbox.width, m_headHitbox.height));
  head.setFillColor(Color::Cyan);
  return head;
}

RectangleShape PlayableCharacter::leftArmHitboxDrawable() {
  RectangleShape arm;
  arm.setPosition(m_leftArmHitbox.left, m_leftArmHitbox.top);
  arm.setSize(Vector2f(m_leftArmHitbox.width, m_leftArmHitbox.height));
  arm.setFillColor(Color::Green);
  return arm;
}

RectangleShape PlayableCharacter::rightArmHitboxDrawable() {
  RectangleShape arm;
  arm.setPosition(m_rightArmHitbox.left, m_rightArmHitbox.top);
  arm.setSize(Vector2f(m_rightArmHitbox.width, m_rightArmHitbox.height));
  arm.setFillColor(Color::Green);
  return arm;
}
