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
    // runs game creating window etc. and starting game loop
    void run();

  private:
    // handles global events outside of all game states
    void handleEvents();
    // updates globaly outside of all game states
    void update(float deltaTime);
    // renders globaly outside of all game states
    void render();
    // recreates the window and updates tells each state where the new window is
    void recreateWindow();

  private:
    // Main window settings for game
    WindowSettings m_windowSettings;
    // Window owned by game
    std::unique_ptr<sf::RenderWindow> m_window;
    // State manager for game
    StateManager m_states;
    // Resource manager for game
    ResourceManager m_resources;
};