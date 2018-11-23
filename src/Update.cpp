#include "headers/Engine.h"

void Engine::update(float elapsedTime) {

  if (m_menuActive) {

  }

  if (m_playing) {
    // TODO: update stuff here

    // We update our current times first
    m_timeSinceSwitch += elapsedTime;

    if (m_isHuman) {
      m_currentLevel.detectCollision(m_human);
      m_human.update(elapsedTime);
      m_demon.setPosition(m_human.getSprite().getPosition());
      m_demon.setHealth(m_human.getHealth());
    } else {
      m_currentLevel.detectCollision(m_demon);
      m_demon.update(elapsedTime);
      m_human.setPosition(m_demon.getSprite().getPosition());
      m_human.setHealth(m_demon.getHealth());
    }

    // First, if we need to fetch a new level, we do so
    if (m_directionToMove != Direction::NONE) {
      // We set the player location, update the current level
      cout << "New Level" << endl;
      m_currentLevel = m_levels.get(m_directionToMove);

      // We now update the player's location
      Vector2f newPosition = m_currentLevel.getStartingLocation(m_directionToMove);

      // We want to spawn both characters, even if we are only playing one
      m_human.spawn(newPosition);
      m_demon.spawn(newPosition);

      // Now we reset our direction so we don't repeatedly move
      m_directionToMove = Direction::NONE;

    }
  }
}
