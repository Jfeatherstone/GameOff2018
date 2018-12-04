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

  m_window.create(VideoMode(resolution.x, resolution.y), "Keith", Style::Default);

  // This should limit the framerate and provide more stable animations
  m_window.setFramerateLimit(60);

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

  // We want to set up the blackout layer here
  m_blackout.setTexture(TextureHolder::getTexture("graphics/blackout.png"));
  m_blackout.setColor(Color(0, 0, 0, 128));
  m_blackout.setOrigin(m_blackout.getLocalBounds().width / 2, m_blackout.getLocalBounds().height / 2);

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
  m_finalScoreText.setFont(font);

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

  rect = m_finalScoreText.getLocalBounds();
  m_finalScoreText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
  m_finalScoreText.setPosition(m_windowSize.x / 2, 200);
  m_finalScoreText.setFillColor(Color::Blue);

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

  // For performance testing
  /*
  11-28-18 Test:
  Not moving:
    Average time for input(): .00210s
    Average time for update(): .0000717s
    Average time for draw(): .0231s *Largest Impact*
  Moving around:
    Average time for input(): .000866s
    Average time for update(): .0000612s
    Average time for draw(): .0177s *Largest Impact*
  Moving + transformations:
    Average time for input(): .000898s
    Average time for update(): .0000375s
    Average time for draw(): .0147s *Largest Impact*

  I have no idea why moving and transformation actually *increases* the performance,
  but we can certainly conclude the draw function is the most impactful across
  the board.

  For I assume similar reasons, the draw() benchmarks are faster while the you are
  the demon character, even though we have to render more objects ????

  */
  Clock benchmark;
  Vector3f avg;
  int n = 1;

  // Our game loop
  while (m_window.isOpen()) {
    dt = clock.restart();
    benchmark.restart();

    input(dt.asSeconds());
    avg.x += benchmark.restart().asSeconds();
    update(dt.asSeconds());
    avg.y += benchmark.restart().asSeconds();
    draw(dt.asSeconds());
    avg.z += benchmark.restart().asSeconds();
    sf::Event event;
    while (m_window.pollEvent(event)) {} // You need an event loop to avoid unreponsive window

    // The framerate
    //cout << 1 / dt.asSeconds() << endl;

    n++;
    if (n >= 10) {
      n = 1;
      //cout << avg.x / 10 << " " << avg.y / 10 << " " << avg.z / 10 << endl;
      avg.x = avg.y = avg.z = 0;
    }
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
