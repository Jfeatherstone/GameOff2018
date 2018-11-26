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
  */
  if (m_currentLevel.getLevelSize().x * Level::TILE_SIZE > m_windowSize.x
    && m_currentLevel.getLevelSize().y * Level::TILE_SIZE < m_windowSize.y
    && m_human.getCenter().x >= m_windowSize.x / 2) {
      //cout << "x larger" << endl;
      m_mainView.setCenter(m_human.getCenter().x, m_windowSize.y / 2);
  } else if (m_currentLevel.getLevelSize().x * Level::TILE_SIZE < m_windowSize.x
    && m_currentLevel.getLevelSize().y * Level::TILE_SIZE > m_windowSize.y
    && m_human.getCenter().y >= m_windowSize.y / 1.2) {
      //cout << "y larger" << endl;
      m_mainView.setCenter(m_windowSize.x / 2, m_human.getCenter().y);
  } else if (m_currentLevel.getLevelSize().x * Level::TILE_SIZE > m_windowSize.x
    && m_currentLevel.getLevelSize().y * Level::TILE_SIZE > m_windowSize.y) {
      m_mainView.setCenter(m_human.getCenter().x, m_human.getCenter().y);
  } else {
      m_mainView.setCenter(m_windowSize.x / 2, m_windowSize.y / 2);
  }

  m_window.setView(m_mainView);
  m_window.draw(m_currentLevel.getVertexArray(),
   &TextureHolder::getTexture(m_currentLevel.getTileSheetPath()));
  m_window.draw(currentChar);

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

  /***** END HUD VIEW *****/

  if (m_menuActive) {
    /***** MENU VIEW *****/
    m_window.setView(m_menuView);
    m_window.draw(m_resumeText);
    m_window.draw(m_exitText);
  }
  /***** END MENU VIEW *****/

  m_window.display();
}
