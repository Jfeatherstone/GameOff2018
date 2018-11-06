#include "headers/Engine.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Engine::Engine() {
  // Fisrt, we setup our window to be the right dimensions, fetching them from
  // the data about the screen
  Vector2f resolution;
  resolution.x = VideoMode::getDesktopMode().width / 1.5;
  resolution.y = VideoMode::getDesktopMode().height / 1.5;

  m_window.create(VideoMode(resolution.x, resolution.y), "Github Game Off 2018", Style::Default);

  // Setup our views with their proper sizes, which are all the same
  m_mainView.setSize(resolution);
  m_HUDView.setSize(resolution);
  m_menuView.setSize(resolution);
  m_BGView.setSize(resolution);
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
