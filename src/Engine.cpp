#include "headers/Engine.h"

using namespace sf;

Engine::Engine() {
  // Fisrt, we setup our window to be the right dimensions, fetching them from
  // the data about the screen
  Vector2f resolution;

  // This is probably not the best way to adjust screen size, but it will give
  // us a consistent set of sizes to work with, as opposed to a ratio which would
  // be slightly different for every monitor
  if (VideoMode::getDesktopMode().width >= 1224 && VideoMode::getDesktopMode().height >= 800) {
    resolution.x = 1024;
    resolution.y = 600;
  } else {
    resolution.x = 640;
    resolution.y = 480;
  }
  m_windowSize.x = resolution.x;
  m_windowSize.y = resolution.y;

  m_window.create(VideoMode(resolution.x, resolution.y), "Github Game Off 2018", Style::Default);

  // Setup our views with their proper sizes, which are all the same
  FloatRect reset(0, 0, resolution.x, resolution.y);
  m_mainView.setSize(resolution);
  m_mainView.reset(reset);
  m_HUDView.setSize(resolution);
  m_HUDView.reset(reset);
  m_menuView.setSize(resolution);
  m_menuView.reset(reset);
  m_BGView.setSize(resolution);
  m_BGView.reset(reset);

  // We also need to load our sprites for the HUD here
  m_healthBorder.setTexture(TextureHolder::getTexture("graphics/health_border.png"));
  m_healthBorder.setOrigin(m_healthBorder.getLocalBounds().width / 2,
   m_healthBorder.getLocalBounds().height / 2);
  m_healthBorder.setPosition(100, 50);
  m_healthBorder.setScale(1.5, 1.5);
  for (int i = 0; i < 4; i++) {
    // We initialize this as human because that's who we start as
    // It doesn't really matter though as their both the same size.
    //cout << m_human.getHealthTexturePath() << endl;
    m_health[i].setTexture(TextureHolder::getTexture(m_human.getHealthTexturePath()));
    // We also set the origin so we can rotate the image properly
    m_health[i].setOrigin(m_health[i].getLocalBounds().width / 2,
     m_health[i].getLocalBounds().height / 2);
    // Since we left room in our sprites, we can set them all at the same point
    m_health[i].setPosition(100, 50);
  }

  // TODO: rotate the four health points to fit in the frame
  // We don't need to do anything to the first one

  // We need to vertically flip the second one
  m_health[0].setScale(1.5, 1.5);
  m_health[1].setScale(-1.5, 1.5);
  m_health[2].setScale(1.5, -1.5);
  m_health[3].setScale(-1.5, -1.5);

  loadLevels();
  m_currentLevel = m_levels.getOrigin();

  // We now update the player's location
  Vector2f newPosition = m_currentLevel.getStartingLocation(Direction::START);
  // We want to spawn both characters, even if we are only playing one
  m_human.spawn(newPosition);
  m_demon.spawn(newPosition);


  // We now want to setup our pause menu
  font.loadFromFile("fonts/Pixellari.ttf");
  m_resumeText.setFont(font);
  m_exitText.setFont(font);
  m_resetText.setFont(font);
  m_messageText.setFont(font);
  m_scoreText.setFont(font);

  m_resumeText.setString("Resume");
  m_exitText.setString("Exit");
  m_resetText.setString("Reset");
  m_messageText.setString("Paused!");

  FloatRect rect = m_resumeText.getLocalBounds();
  m_resumeText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
  m_resumeText.setPosition(m_windowSize.x / 2, m_windowSize.y / 2 - 36);
  m_resumeText.setFillColor(Color::Red);

  rect = m_exitText.getLocalBounds();
  m_exitText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
  m_exitText.setPosition(m_windowSize.x / 2, m_windowSize.y / 2 + 36);
  m_exitText.setFillColor(Color::Red);

  rect = m_resetText.getLocalBounds();
  m_resetText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
  m_resetText.setPosition(m_windowSize.x / 2, m_windowSize.y / 2);
  m_resetText.setFillColor(Color::Red);

  rect = m_messageText.getLocalBounds();
  m_messageText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
  m_messageText.setPosition(m_windowSize.x / 2, 150);
  m_messageText.setFillColor(Color::Blue);

  rect = m_scoreText.getLocalBounds();
  m_scoreText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
  m_scoreText.setPosition(1 * m_windowSize.x / 6, 25);
  m_scoreText.setCharacterSize(45);
  m_scoreText.setFillColor(Color::White);
}

void Engine::run() {
  // Setup our timer
  Clock clock;
  Time dt;

  // Our game loop
  while (m_window.isOpen()) {
    dt = clock.restart();

    input(dt.asSeconds());
    update(dt.asSeconds());
    draw();
  }
}

void Engine::loadLevels() {
  string folderPath = "levels";
  // First we find out how many files we have
  for (auto& file: fs::directory_iterator(folderPath)) {
    stringstream ss;
    ss << file;
    // The substring nonsense is to remove the quotes at the beg and end of the str
    Level level = Level::loadLevel(ss.str().substr(1, ss.str().length() - 2));
    level.printLevel();
    // Add our level to the list
    m_levels.addAt(level, level.getMapLocation());
  }

}
