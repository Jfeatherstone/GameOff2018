#include "headers/Engine.h"

void Engine::input(float elapsedTime) {

  // Accessing the menu
  if (Keyboard::isKeyPressed(Keyboard::Escape) && m_timeSincePause > .5) {
    m_timeSincePause = 0;
    m_menuActive = !m_menuActive;
    m_playing = !m_playing;
    //m_window.close();
  }

  if (m_menuActive) {
    // We first want to highlight the text we scroll over
    Vector2i pos = Mouse::getPosition(m_window);
    // This just automatically adjusts the position relative to the window

    FloatRect resume = m_resumeText.getGlobalBounds();
    FloatRect exit = m_exitText.getGlobalBounds();
    //cout << pos.x << " " << pos.y << endl;
    //cout << resume.left << " " << resume.top << endl;

    if ((pos.x > resume.left && pos.x < resume.left + resume.width)
        && (pos.y > resume.top && pos.y < resume.top + resume.height))
      m_resumeText.setFillColor(Color::White);
    else
      m_resumeText.setFillColor(Color::Red);

    if ((pos.x > exit.left && pos.x < exit.left + exit.width)
        && (pos.y > exit.top && pos.y < exit.top + exit.height))
      m_exitText.setFillColor(Color::White);
    else
      m_exitText.setFillColor(Color::Red);

    // Listen for mouse clicks on the buttons
    if (Mouse::isButtonPressed(Mouse::Left)) {
      // We want to see if it intersects our buttons

      // Resume
      if ((pos.x > exit.left && pos.x < exit.left + exit.width)
          && (pos.y > exit.top && pos.y < exit.top + exit.height))
          m_window.close();

      if ((pos.x > resume.left && pos.x < resume.left + resume.width)
          && (pos.y > resume.top && pos.y < resume.top + resume.height)) {
        m_menuActive = false;
        m_playing = true;
      }

    }
  }

  // Gameplay specific stuff goes in here
  if (m_playing) {

    // If the player wants to switch characters
    if (Keyboard::isKeyPressed(Keyboard::E)) {
      // We also want to make sure the player doesn't switch too often
      if (m_timeSinceSwitch >= m_playerSwitchCooldown) {
        m_isHuman = !m_isHuman;
        m_timeSinceSwitch = 0;
      }
    }

    // We will handle character specific movements in their own classes
    if (m_isHuman)
      m_human.handleInput(elapsedTime);
    else
      m_demon.handleInput(elapsedTime);
  }
}
