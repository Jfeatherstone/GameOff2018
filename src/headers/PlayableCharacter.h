#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include <iostream>

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
  string m_name;

  /*
  // Probably won't have health regen because of the health system above
  // The player will have passive regen at a fixed rate
  float m_regenRate = .04f;
  // The player will recover this % of their health every second
  */

  // Our sprite, which will be different for the two characters
  Sprite m_characterSprite;

  // We will also have two different health bars for each character, one of
  // them will be dark and the other light. I'm not sure if there will be
  // a functional difference yet, maybe certain attacks don't damage each one
  string m_healthTexturePath;

  // Bools for determining where the player is in respect to the level
  bool m_onGround;
  bool m_inAir;
  bool m_jumping;

  // To differentiate our characters, we are going to use the variable canFly
  bool m_canFly;
  // If this value is true, it means we are the second character, meaning
  // we aren't allowed to touch the ground

  // The jump duration of the character. For our first character, this will
  // be how long their jump is from the ground, and for the second character, this
  // is how long their flying movement is.
  float m_jumpDuration;
  float m_currentJumpTime;

  // The rectangles that represent the player's hitboxes for different parts of
  // their bodies. The second character will have two extra because of the wings
  FloatRect m_headHitbox;
  FloatRect m_feetHitbox;
  FloatRect m_leftArmHitbox;
  FloatRect m_rightArmHitbox;
  FloatRect m_leftWingHitbox;
  FloatRect m_rightWingHitbox;

  // Our character's location
  Vector2f m_position;

  // We also need a way to keep track of whether our character is moving
  // Since we want a little bit of acceleration, we use floats instead of booleans
  float m_velocity = 0;
  float m_startingVelocity = 1000;
  // Our acceleration, which is 350% each second up to 130%
  float m_acceleration = 3.5f;
  float m_accelerationCap = 1.5f;

public:
  // The handleInput function that will be different for each, which is why its virtual
  bool virtual handleInput(float elapsedTime) = 0;

  void update(float elapsedTime);
  void spawn(Vector2f position);

  // Some basic getters
  Sprite getSprite();
  int getHealth();
  string getHealthTexturePath();
  void setPosition(Vector2f position);
};
