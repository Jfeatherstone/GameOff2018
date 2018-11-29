#include "headers/Engine.h"

void Engine::input(float elapsedTime) {

  //cout << Joystick::isConnected(0) << endl;

  // Accessing the menu
  if (Keyboard::isKeyPressed(Keyboard::Escape) && m_timeSincePause > .5) {
    m_timeSincePause = 0;
    m_menuActive = !m_menuActive;
    m_playing = !m_playing;
    //m_window.close();
    if (m_messageText.getString() == "You died!") {
      m_messageText.setString("Paused");
      FloatRect rect = m_messageText.getLocalBounds();
      m_messageText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
      m_messageText.setPosition(m_windowSize.x / 2, 150);
    }
    m_finalScoreText.setString("");
  }

  if (m_menuActive) {
    // We first want to highlight the text we scroll over
    Vector2i pos = Mouse::getPosition(m_window);
    // This just automatically adjusts the position relative to the window

    FloatRect resume = m_resumeText.getGlobalBounds();
    FloatRect exit = m_exitText.getGlobalBounds();
    FloatRect reset = m_resetText.getGlobalBounds();
    //cout << pos.x << " " << pos.y << endl;
    //cout << resume.left << " " << resume.top << endl;

    if ((pos.x > resume.left && pos.x < resume.left + resume.width)
        && (pos.y > resume.top && pos.y < resume.top + resume.height))
      m_resumeText.setFillColor(Color::White);
    else
      m_resumeText.setFillColor(Color::Red);

    if ((pos.x > reset.left && pos.x < reset.left + reset.width)
        && (pos.y > reset.top && pos.y < reset.top + reset.height))
      m_resetText.setFillColor(Color::White);
    else
      m_resetText.setFillColor(Color::Red);

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

      if ((pos.x > reset.left && pos.x < reset.left + reset.width)
          && (pos.y > reset.top && pos.y < reset.top + reset.height)) {
            m_currentLevel = m_levels.getOrigin();
            Vector2f newPosition = m_currentLevel.getStartingLocation(Direction::START);
            // We want to spawn both characters, even if we are only playing one
            m_human.spawn(newPosition);
            m_demon.spawn(newPosition);

            // Now we reset our direction so we don't repeatedly move
            m_human.setDirectionToMove(Direction::NONE);
            m_demon.setDirectionToMove(Direction::NONE);
            m_human.setHealth(4);
            m_demon.setHealth(4);

            m_human.setScore(0);
            m_demon.setScore(0);

            if (m_messageText.getString() == "You died!") {
              m_messageText.setString("Paused");
              FloatRect rect = m_messageText.getLocalBounds();
              m_messageText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
              m_messageText.setPosition(m_windowSize.x / 2, 150);
            }
            m_finalScoreText.setString("");
      }


      if ((pos.x > resume.left && pos.x < resume.left + resume.width)
          && (pos.y > resume.top && pos.y < resume.top + resume.height)) {
        m_menuActive = false;
        m_playing = true;
        if (m_messageText.getString() == "You died!") {
          m_messageText.setString("Paused");
          FloatRect rect = m_messageText.getLocalBounds();
          m_messageText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
          m_messageText.setPosition(m_windowSize.x / 2, 150);
        }
        m_finalScoreText.setString("");
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
