#include "headers/Engine.h"

void Engine::update(float elapsedTime) {

  if (m_menuActive) {

  }

  if (m_playing) {
    // TODO: update stuff here

    // First, if we need to fetch a new level, we do so
    if (m_directionToMove != Direction::NONE) {
      // We set the player location, update the current level

      m_currentLevel = m_levels.get(m_directionToMove);

      // Now we reset our direction so we don't repeatedly move
      m_directionToMove = Direction::NONE;
    }
  }
}
