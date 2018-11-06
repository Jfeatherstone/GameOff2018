#include "headers/Engine.h"

void Engine::input() {

  // Accessing the menu
  if (Keyboard::isKeyPressed(Keyboard::Escape)) {
    m_menuActive = !m_menuActive;
    m_playing = !m_playing;
  }

  // Gameplay specific stuff goes in here
  if (m_playing) {
    
  }
}
