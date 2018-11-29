#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include <iostream>
#include "NLLinkedList.h"

using namespace sf;
using namespace std;

// Most stuff here will be protected so that the other characters can
// inherit it
class PlayableCharacter {
protected:
  // Both characters will have the same health bar, so that can be defined here
  // All attacks will do one tick of damage, out of our 4 health points
  int m_health;
  const int m_maxHealth = 4;

  // Each character will have a different name
  string m_name; // This is unused for now

  // The player's score
  int m_score;

  /*
  // Probably won't have health regen because of the health system above
  // The player will have passive regen at a fixed rate
  float m_regenRate = .04f;
  // The player will recover this % of their health every second
  */

  // Our sprite, which will be different for the two characters
  Sprite m_characterSprite;
  Sprite m_leftWing;
  Sprite m_rightWing;

  int m_wingIndex;
  int m_wingSpeed;
  Vector2f wingSize;
  // We will also have two different health bars for each character, one of
  // them will be dark and the other light. I'm not sure if there will be
  // a functional difference yet, maybe certain attacks don't damage each one
  string m_healthTexturePath;

  // Bools for determining where the player is in respect to the level
  bool m_inAir = true;
  bool m_jumping;
  bool m_falling;

  // To differentiate our characters, we are going to use the variable canFly
  bool m_canFly;
  // If this value is true, it means we are the second character, meaning
  // we aren't allowed to touch the ground

  // The jump duration of the character. For our first character, this will
  // be how long their jump is from the ground, and for the second character, this
  // is how long their flying movement is.
  float m_jumpDuration = .4f;
  float m_currentJumpTime;

  // We don't want the player to get hit with several ticks of damage in successsion
  float m_timeSinceDamage;
  float m_damageCooldown = 1.5f;

  // The rectangles that represent the player's hitboxes for different parts of
  // their bodies. The second character will have two extra because of the wings
  FloatRect m_headHitbox;
  FloatRect m_feetHitbox;
  FloatRect m_leftArmHitbox;
  FloatRect m_rightArmHitbox;

  // Our character's location
  Vector2f m_position;

  // We also need a way to keep track of whether our character is moving
  // Since we want a little bit of acceleration, we use floats instead of booleans
  Vector2f m_velocity;
  float m_startingVelocity;
  // Our acceleration, which is 350% each second up to 130%
  float m_acceleration = 3.5f;
  float m_accelerationCap = 1.5f;
  float m_gravityAcceleration = 1.5f;
  float m_terminalVelocity;
  Direction m_directionToMove = Direction::NONE;

public:
  // The handleInput function that will be different for each, which is why its virtual
  bool virtual handleInput(float elapsedTime) = 0;

  void update(float elapsedTime);
  void updateWings(float elapsedTime);
  void spawn(Vector2f position);

  // Some basic getters
  Sprite getSprite();
  Sprite getLeftWing();
  Sprite getRightWing();

  int getHealth();
  string getHealthTexturePath();
  void setPosition(Vector2f position);
  void setVelocity(Vector2f velocity);
  Vector2f getVelocity();
  FloatRect getPosition();
  void setInAir(bool inAir);
  void setJumping(bool jumping);
  void setFalling(bool falling);
  bool canFly();
  void incrementHealth(int increment);
  void takeDamage(int amount);
  Vector2f getCenter();
  void setHealth(int health);
  void setDirectionToMove(Direction dir);
  Direction getDirectionToMove();
  void setScore(int score);
  int getScore();
  void incrementScore(int increment);
  void setWingIndex(int index);
  int getWingIndex();
  int getWingSpeed();


  // Hitbox stuff
  FloatRect getFeetHitbox();
  FloatRect getHeadHitbox();
  FloatRect getLeftArmHitbox();
  FloatRect getRightArmHitbox();

  RectangleShape feetHitboxDrawable();
  RectangleShape headHitboxDrawable();
  RectangleShape leftArmHitboxDrawable();
  RectangleShape rightArmHitboxDrawable();
  // These two are virtual, because only the demon class has them
  //RectangleShape virtual leftWingHitboxDrawable() = 0;
  //RectangleShape virtual rightWingHitboxDrawable() = 0;

};
