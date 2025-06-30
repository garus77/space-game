// game.h
#pragma once
#include "resourceManager.h"
#include "settings.h"
#include "stateManager.h"
#include <SFML/Graphics.hpp>
#include <memory>

// The class from wich everything runs
class Game
{
  public:
    // Game constructor
    Game();
    // Runs game creating window etc. and starting game loop
    void run();

  private:
    // Handles global events outside of all game states
    void handleEvents();
    // Updates globaly outside of all game states
    void update(float deltaTime);
    // Renders globaly outside of all game states
    void render();
    // Recreates the window and updates tells each state where the new window is
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