#include "headers/Engine.h"

void Engine::update(float elapsedTime) {
  m_timeSincePause += elapsedTime;

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
      m_demon.setDirectionToMove(m_human.getDirectionToMove());
    } else {
      m_currentLevel.detectCollision(m_demon);
      m_demon.update(elapsedTime);
      m_human.setPosition(m_demon.getSprite().getPosition());
      m_human.setHealth(m_demon.getHealth());
      m_human.setDirectionToMove(m_demon.getDirectionToMove());
    }

    // First, if we need to fetch a new level, we do so
    if (m_human.getDirectionToMove() != Direction::NONE || m_demon.getDirectionToMove() != Direction::NONE ) {

      // This should only be here while creating and testing levels
      loadLevels();

      // We set the player location, update the current level
      //cout << "New Level" << endl;
      m_currentLevel = m_levels.get(m_human.getDirectionToMove());
      //cout << DIRECTION_NAMES[m_human.getDirectionToMove()] << endl;
      //m_currentLevel.printLevel();
      // We now update the player's location
      Vector2f newPosition = m_currentLevel.getStartingLocation(m_human.getDirectionToMove());
      //cout << newPosition.x << " " << newPosition.y << endl;
      // This next part is for debugging levels

      if (newPosition.x + m_human.getPosition().width > m_currentLevel.getLevelSize().x * Level::TILE_SIZE)
        cout << "Spawn location outside of level (x - " << newPosition.x << " vs. " << m_currentLevel.getLevelSize().x * Level::TILE_SIZE <<" )" << endl;

      if (newPosition.y + m_human.getPosition().height > m_currentLevel.getLevelSize().y * Level::TILE_SIZE)
        cout << "Spawn location outside of level (y - " << newPosition.y << " vs. " << m_currentLevel.getLevelSize().y * Level::TILE_SIZE <<" )" << endl;

      // We want to spawn both characters, even if we are only playing one
      m_human.spawn(newPosition);
      m_demon.spawn(newPosition);

      // Now we reset our direction so we don't repeatedly move
      m_human.setDirectionToMove(Direction::NONE);
      m_demon.setDirectionToMove(Direction::NONE);

    }

    // If our health drops to 0, we restart the entire map
    if (m_human.getHealth() <= 0) {
      //cout << "Died" << endl;
      m_currentLevel = m_levels.getOrigin();
      Vector2f newPosition = m_currentLevel.getStartingLocation(Direction::START);

      // We want to spawn both characters, even if we are only playing one
      m_human.spawn(newPosition);
      m_demon.spawn(newPosition);

      // And pause the game
      m_human.setHealth(4);
      m_demon.setHealth(4);
    }
  }
}
