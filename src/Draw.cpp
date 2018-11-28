#include "headers/Engine.h"

void drawHUD();

void Engine::draw() {
  m_window.clear();

  // We want to make sure that we are using the proper sprites for our character
  Sprite currentChar = (m_isHuman) ? m_human.getSprite() : m_demon.getSprite();
  string healthTexture = (m_isHuman) ? m_human.getHealthTexturePath() : m_demon.getHealthTexturePath();

  /***** BACKGROUND VIEW *****/
  m_window.setView(m_BGView);
  m_window.draw(m_currentLevel.getBackground());

  /***** END BACKGROUND VIEW *****/

  /***** MAIN VIEW *****/
  // We want to have a dynamic camera in case our levels are big
  /*
  The reason this is such a clown fiesta is because we want to be able to give
  the user the most amount of screen possible. If we are close to the edge of the
  levels, we want to not center on the player, but otherwise we do

  I sincerely apologize to anyone who even looks at this next section
  When I wrote this, only God and I understood it, and now, only God does

  */
  if (m_currentLevel.getLevelSize().x * Level::TILE_SIZE > m_windowSize.x
    && m_currentLevel.getLevelSize().y * Level::TILE_SIZE < m_windowSize.y
    && m_human.getCenter().x >= m_windowSize.x / 2) {
      //cout << "x larger" << endl;
      if (m_human.getCenter().x >= m_currentLevel.getLevelSize().x * Level::TILE_SIZE - m_windowSize.x / 2) {
        m_mainView.setCenter(m_currentLevel.getLevelSize().x * Level::TILE_SIZE - m_windowSize.x / 2, m_windowSize.y / 2);
      } else
        m_mainView.setCenter(m_human.getCenter().x, m_windowSize.y / 2);
  } else if (m_currentLevel.getLevelSize().x * Level::TILE_SIZE < m_windowSize.x
    && m_currentLevel.getLevelSize().y * Level::TILE_SIZE > m_windowSize.y
    && (m_human.getCenter().y >= m_windowSize.y / 1.2)) {
      //cout << "y larger" << endl;
      if (m_human.getCenter().x >= m_currentLevel.getLevelSize().x * Level::TILE_SIZE - m_windowSize.x / 2)
        m_mainView.setCenter(m_windowSize.x / 2, m_currentLevel.getLevelSize().y * Level::TILE_SIZE - m_windowSize.y / 2);
      else
        m_mainView.setCenter(m_windowSize.x / 2, m_human.getCenter().y);
  } else if (m_currentLevel.getLevelSize().x * Level::TILE_SIZE > m_windowSize.x
    && m_currentLevel.getLevelSize().y * Level::TILE_SIZE > m_windowSize.y) {
      float xPos = m_human.getCenter().x;
      float yPos = m_human.getCenter().y;
      if (m_human.getCenter().x >= m_currentLevel.getLevelSize().x * Level::TILE_SIZE - m_windowSize.x / 2)
        xPos = m_currentLevel.getLevelSize().x * Level::TILE_SIZE - m_windowSize.x / 2;
      if (m_human.getCenter().y >= m_currentLevel.getLevelSize().y * Level::TILE_SIZE - m_windowSize.y / 2)
        yPos = m_currentLevel.getLevelSize().y * Level::TILE_SIZE - m_windowSize.y / 2;
      if (m_human.getCenter().x <= m_windowSize.x / 2)
        xPos = m_windowSize.x / 2;
      if (m_human.getCenter().y <= m_windowSize.y / 2)
        yPos = m_windowSize.y / 2;

      m_mainView.setCenter(xPos, yPos);
  } else {
      //cout << m_human.getCenter().x << " " << m_currentLevel.getLevelSize().x * Level::TILE_SIZE - m_windowSize.x / 2 << endl;
      m_mainView.setCenter(m_windowSize.x / 2, m_windowSize.y / 2);
  }

  m_window.setView(m_mainView);
  m_window.draw(m_currentLevel.getVertexArray(),
   &TextureHolder::getTexture(m_currentLevel.getTileSheetPath()));
  m_window.draw(currentChar);
  // We also want to draw our coins here too
  if (m_isHuman) {
    for (auto element: m_currentLevel.getLightCoins()) {
      Sprite coin;
      coin.setTexture(TextureHolder::getTexture("graphics/light_coin.png"));
      coin.setPosition(element.x * Level::TILE_SIZE, element.y * Level::TILE_SIZE);
      m_window.draw(coin);
    }
  } else {
    for (auto element: m_currentLevel.getDarkCoins()) {
      Sprite coin;
      coin.setTexture(TextureHolder::getTexture("graphics/dark_coin.png"));
      coin.setPosition(element.x * Level::TILE_SIZE, element.y * Level::TILE_SIZE);
      m_window.draw(coin);
    }
}

  // For debugging our hitboxes
  /*
  if (m_isHuman) {
    m_window.draw(m_human.feetHitboxDrawable());
    m_window.draw(m_human.headHitboxDrawable());
    m_window.draw(m_human.leftArmHitboxDrawable());
    m_window.draw(m_human.rightArmHitboxDrawable());
  } else {
    m_window.draw(m_demon.feetHitboxDrawable());
    m_window.draw(m_demon.headHitboxDrawable());
    m_window.draw(m_demon.leftArmHitboxDrawable());
    m_window.draw(m_demon.rightArmHitboxDrawable());
  }
  */
  /***** END MAIN VIEW *****/

  /***** HUD VIEW *****/
  m_window.setView(m_HUDView);
  m_window.draw(m_healthBorder);
  // Again, human isn't used for any particular reason, as both should always be in sync
  // We count backwards to make sure the right health are filled in
  for (int i = 3; i > 3 - m_human.getHealth(); i--) {
    m_health[i].setTexture(TextureHolder::getTexture(healthTexture));
    m_window.draw(m_health[i]);
  }
  // We also want to draw the score
  stringstream ss;
  ss << "Score: " << m_human.getScore();
  m_scoreText.setString(ss.str());
  m_window.draw(m_scoreText);

  /***** END HUD VIEW *****/

  if (m_menuActive) {
    /***** MENU VIEW *****/
    m_window.setView(m_menuView);
    m_window.draw(m_resumeText);
    m_window.draw(m_exitText);
    m_window.draw(m_resetText);
    m_window.draw(m_messageText);
    m_window.draw(m_finalScoreText);
  }
  /***** END MENU VIEW *****/

  m_window.display();
}
