#include "headers/Engine.h"

void Engine::update(float elapsedTime) {
  m_timeSincePause += elapsedTime;

  if (m_menuActive) {

  }

  if (m_playing) {
    // TODO: update stuff here

    // We update our current times first
    m_timeSinceSwitch += elapsedTime;

    if (!transition) {
      if (m_isHuman) {
        m_currentLevel.detectCollision(m_human);
        m_human.update(elapsedTime);
        m_demon.setPosition(m_human.getSprite().getPosition());
        m_demon.setHealth(m_human.getHealth());
        m_demon.setDirectionToMove(m_human.getDirectionToMove());
        m_demon.setScore(m_human.getScore());
      } else {
        m_currentLevel.detectCollision(m_demon);
        m_demon.update(elapsedTime);
        m_human.setPosition(m_demon.getSprite().getPosition());
        m_human.setHealth(m_demon.getHealth());
        m_human.setDirectionToMove(m_demon.getDirectionToMove());
        m_human.setScore(m_demon.getScore());
      }

      // First, if we need to fetch a new level, we do so
      if (m_human.getDirectionToMove() != Direction::NONE || m_demon.getDirectionToMove() != Direction::NONE ) {

        // This should only be here while creating and testing levels
        //loadLevels();

        // First, we want to save the changes to the level we are in (coins gotten)
        m_levels.addAt(m_currentLevel, m_currentLevel.getMapLocation());

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

        m_playing = false;
        m_menuActive = true;

        m_messageText.setString("You died!");
        stringstream ss;
        ss << "Score: " << m_human.getScore();
        m_finalScoreText.setString(ss.str());

        FloatRect rect = m_messageText.getLocalBounds();
        m_messageText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
        m_messageText.setPosition(m_windowSize.x / 2, 150);

        rect = m_finalScoreText.getLocalBounds();
        m_finalScoreText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
        m_finalScoreText.setPosition(m_windowSize.x / 2, 200);

        m_isHuman = true;

        m_human.setScore(0);
        m_demon.setScore(0);
        // Reset the coins
        loadLevels();
      }
    }

    if (m_timeSinceSwitch <= 1 && !transition) {
      //cout << "transition" << endl;
      transition = true;
      m_blackout.setColor(Color(0, 0, 0, m_opacity = 0));
      if (m_isHuman) {
        m_demon.setWingIndex(14 * m_demon.getWingSpeed());
        m_wingIncrement = 1;
        m_maxWingIndex = 29 * m_demon.getWingSpeed();
      } else {
        m_demon.setWingIndex(29 * m_demon.getWingSpeed());
        m_wingIncrement = -1;
        m_maxWingIndex = 14 * m_demon.getWingSpeed();
      }
    } else if (m_timeSinceSwitch > 1 && transition) {
      transition = false;
      m_demon.setWingIndex(0);
    }

  }
}
