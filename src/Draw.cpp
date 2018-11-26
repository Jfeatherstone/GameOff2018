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

  /***** MENU VIEW *****/
  m_window.setView(m_menuView);

  /***** END MENU VIEW *****/

  m_window.display();
}
