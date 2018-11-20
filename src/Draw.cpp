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
  m_window.setView(m_mainView);
  m_window.draw(m_currentLevel.getVertexArray(),
   &TextureHolder::getTexture(m_currentLevel.getTileSheetPath()));
  m_window.draw(currentChar);
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
