// game.h
#pragma once
#include "resourceManager.h"
#include "settings.h"
#include "stateManager.h"
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
    void recreateWindow();

  private:
    WindowSettings m_windowSettings;
    std::unique_ptr<sf::RenderWindow> m_window;
    StateManager m_states;
    ResourceManager m_resources;
};