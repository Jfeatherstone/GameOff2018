#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Level.h"

using namespace sf;

class Engine {
private:
  const int TILE_SIZE = 25;
  const int VERTS_IN_QUAD = 4;

  // TODO: have the player accelerate as they fall
  const int GRAVITY = 300;

  // Our display window
  RenderWindow m_window;

  // We only need one view for the main character, one for the HUD, one
  // for the background, and one for the pause menu
  View m_mainView;
  View m_BGView;
  View m_HUDView;
  View m_menuView;

  // If the menu is shown
  bool m_menuActive;

  // This will be false when we are swapping levels, paused, etc.
  bool m_playing = true;

  // This will signify whether the player is the first or second character
  bool m_player1;
  // There has to be some cooldown for switching characters
  float m_playerSwitchCooldown = 2;
  // And a tracker for how long it's been
  float m_timeSinceSwitch;
  
  // Our current level
  Level m_currentLevel;

  // Our abstracted functions
  // These are defined in their own files according to their name
  void input();
  void draw();
  void update(float elapsedTime);
  void loadLevel();

public:
  Engine();

  void run();

};
