#include "headers/Engine.h"

void drawHUD();

Clock benchmark;

void Engine::draw(float elapsedTime) {
  // These are both for benchmark tests
  bool benchmarkTesting = false;
  Vector3f avg;

  m_window.clear();

  // We want to make sure that we are using the proper sprites for our character
  Sprite currentChar = (m_isHuman) ? m_human.getSprite() : m_demon.getSprite();
  string healthTexture = (m_isHuman) ? m_human.getHealthTexturePath() : m_demon.getHealthTexturePath();

  /***** BACKGROUND VIEW *****/
  if (benchmarkTesting)
    benchmark.restart();

  m_window.setView(m_BGView);
  m_window.draw(m_currentLevel.getBackground());

  /***** END BACKGROUND VIEW *****/
  if (benchmarkTesting)
    avg.x = benchmark.restart().asSeconds();

  /***** MAIN VIEW *****/
  if (benchmarkTesting)
    benchmark.restart();
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
  // Draw our wings if we are the demon
  if (!m_isHuman && !transition) {
    m_window.draw(m_demon.getLeftWing());
    m_window.draw(m_demon.getRightWing());
  }

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

  // If we are transitioning, we want to fade out the screen
  if (transition) {
    //cout << m_timeSinceSwitch << endl;
    if (m_timeSinceSwitch > .5f) {
      m_blackout.setColor(Color(0, 0, 0, m_opacity -= (m_opacity) * 4 * elapsedTime));
    }
    if (m_timeSinceSwitch < .5f) {
      m_blackout.setColor(Color(0, 0, 0, m_opacity += (255 - m_opacity) * 4 * elapsedTime));
    }
    //cout << m_demon.getWingIndex() << endl;
    m_demon.updateWings(elapsedTime);
    m_blackout.setPosition(m_human.getCenter());
    m_window.draw(m_blackout);
    m_window.draw(m_demon.getLeftWing());
    m_window.draw(m_demon.getRightWing());
    if (m_demon.getWingIndex() != m_maxWingIndex)
      m_demon.setWingIndex(m_demon.getWingIndex() + m_wingIncrement);

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
  if (benchmarkTesting)
    avg.y = benchmark.restart().asSeconds();

  /***** HUD VIEW *****/
  if (benchmarkTesting)
    benchmark.restart();

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
  if (benchmarkTesting)
    avg.z = benchmark.restart().asSeconds();


  if (m_menuActive) {
    /***** MENU VIEW *****/
    m_window.setView(m_menuView);
    m_window.draw(m_resumeText);
    m_window.draw(m_exitText);
    m_window.draw(m_resetText);
    m_window.draw(m_messageText);
    m_window.draw(m_finalScoreText);
    m_window.draw(m_controlsText1);
    m_window.draw(m_controlsText2);    
  }
  /***** END MENU VIEW *****/

  m_window.display();

  if (benchmarkTesting)
    cout << avg.x << " " << avg.y << " " << avg.z << endl;
  /*
  Benchmark results:
  Human:
    Background draw time: .00005 - .0001s
    Main draw time: .0021 - .0056s
    HUD draw time: .0024 - .0064s

  */

}
