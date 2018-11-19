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
  drawHUD();
  /***** END HUD VIEW *****/

  /***** MENU VIEW *****/
  m_window.setView(m_menuView);

  /***** END MENU VIEW *****/

  m_window.display();
}

void drawHUD() {

}
