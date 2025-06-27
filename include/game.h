#pragma once
#include "settings.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Game
{
  public:
    Game();
    void run();

  private:
    void handleEvents();
    void update(float deltaTime);
    void render();

  private:
    std::unique_ptr<sf::RenderWindow> m_window;
    WindowSettings m_settings;
};