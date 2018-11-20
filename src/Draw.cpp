#include "headers/Engine.h"

void drawHUD();

void Engine::draw() {
  m_window.clear();

  /***** BACKGROUND VIEW *****/
  m_window.setView(m_BGView);
  m_window.draw(m_currentLevel.getBackground());

  /***** END BACKGROUND VIEW *****/

  /***** MAIN VIEW *****/
  m_window.setView(m_mainView);
  m_window.draw(m_currentLevel.getVertexArray(),
   &TextureHolder::getTexture(m_currentLevel.getTileSheetPath()));

  /***** END MAIN VIEW *****/

  /***** HUD VIEW *****/
  m_window.setView(m_HUDView);
  m_window.draw(m_healthBorder);
  // Again, human isn't used for any particular reason, as both should always be in sync
  // We count backwards to make sure the right health are filled in
  for (int i = m_human.getHealth() - 1; i >= 0; i--)
    m_window.draw(m_health[i]);
  //m_window.draw(m_health[0]);

  /***** END HUD VIEW *****/

  /***** MENU VIEW *****/
  m_window.setView(m_menuView);

  /***** END MENU VIEW *****/

  m_window.display();
}
