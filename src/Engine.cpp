#include "headers/Engine.h"
#include <SFML/Graphics.hpp>

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
  m_mainView.setSize(resolution);
  m_HUDView.setSize(resolution);
  m_menuView.setSize(resolution);
  m_BGView.setSize(resolution);

  loadLevels();
}

void Engine::run() {
  // Setup our timer
  Clock clock;
  Time dt;

  // Our game loop
  while (m_window.isOpen()) {
    dt = clock.restart();

    input();
    update(dt.asSeconds());
    draw();
  }
}

void Engine::loadLevels() {
  string folderPath = "levels";
  int numFiles = 0;
  // First we find out how many files we have
  for (auto& file: fs::directory_iterator(folderPath)) {
    numFiles++;
    stringstream ss;
    ss << file;
    // The substring nonsense is to remove the quotes at the beg and end of the str
    Level level = Level::loadLevel(ss.str().substr(1, ss.str().length() - 2));
    level.printLevel();
    // Add our level to the list
    m_levels.addAt(level, level.getMapLocation());
  }
  m_currentLevel = m_levels.getOrigin();
  m_directionToMove = Direction::NONE;
}
